#include "gtest/gtest.h"

#include "rapidjson/document.h"

#include "../tree_Folder.h"
#include "../tree_Disk.h"

#include <memory>
#include <sstream>

#include "data.h"

TEST(Folder, Initialization)
{
	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name": "folder"})"));

		std::unique_ptr<tree::Folder> ptr { tree::Folder::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"content": []})"));

		std::unique_ptr<tree::Folder> ptr { tree::Folder::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name": "folder", "content": []})"));

		std::unique_ptr<tree::Folder> ptr { tree::Folder::Parse(json) };
		EXPECT_NE(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"([])"));

		std::unique_ptr<tree::Folder> ptr { tree::Folder::Parse(json) };
		EXPECT_NE(ptr.get(), nullptr);
	}
}

TEST(Folder, Size)
{
	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(data::json_str));

	std::unique_ptr<tree::Folder> ptr { tree::ParseDisk(json) };
	EXPECT_NE(ptr.get(), nullptr);

	EXPECT_DOUBLE_EQ((double)ptr->Size(false, false), 4);

	EXPECT_DOUBLE_EQ((double)ptr->Size(true, false), 44);

	EXPECT_DOUBLE_EQ((double)ptr->Size(false, true), (64 + 8 + 128) + ((2 + 16) + 32) + 4);

	EXPECT_DOUBLE_EQ((double)ptr->Size(true, true), (64 + 8 + 128) + ((2 + 16 + (64 + 8 + 128)) + 32) + 4 + ((2 + 16 + (64 + 8 + 128)) + 32) + 8);
}

TEST(Folder, List)
{
	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(data::json_str));

	std::unique_ptr<tree::Folder> ptr { tree::ParseDisk(json) };
	EXPECT_NE(ptr.get(), nullptr);

	{
		std::stringstream str;
		ptr->List(false, false, "", str);

		EXPECT_STREQ(str.str().c_str(), R"([]
    [folder-A]
    [folder-B]
    file-X [4]
    link-Y ---> /folder-B
    link-Z ---> /folder-A/file-A-S
)");
	}

	{
		std::stringstream str;
		ptr->List(false, false, "++", str);

		EXPECT_STREQ(str.str().c_str(), R"([]
++    [folder-A]
++    [folder-B]
++    file-X [4]
++    link-Y ---> /folder-B
++    link-Z ---> /folder-A/file-A-S
)");
	}

	{
		std::stringstream str;
		ptr->List(true, false, "", str);

		EXPECT_STREQ(str.str().c_str(), R"([]
    [folder-A]
    [folder-B]
    file-X [4]
    link-Y ---> /folder-B // [folder-B]
        [folder-B-G]
        file-B-M [32]
    link-Z ---> /folder-A/file-A-S // file-A-S [8]
)");
	}

	{
		std::stringstream str;
		ptr->List(false, true, "", str);

		EXPECT_STREQ(str.str().c_str(), R"([]
    [folder-A]
        file-A-R [64]
        file-A-S [8]
        file-A-T [128]
    [folder-B]
        [folder-B-G]
            file-B-G-J [2]
            file-B-G-K [16]
            link-B-G-L ---> /folder-A
        file-B-M [32]
    file-X [4]
    link-Y ---> /folder-B
    link-Z ---> /folder-A/file-A-S
)");
	}

	{
		std::stringstream str;
		ptr->List(true, true, "", str);

		EXPECT_STREQ(str.str().c_str(), R"([]
    [folder-A]
        file-A-R [64]
        file-A-S [8]
        file-A-T [128]
    [folder-B]
        [folder-B-G]
            file-B-G-J [2]
            file-B-G-K [16]
            link-B-G-L ---> /folder-A // [folder-A]
                file-A-R [64]
                file-A-S [8]
                file-A-T [128]
        file-B-M [32]
    file-X [4]
    link-Y ---> /folder-B // [folder-B]
        [folder-B-G]
            file-B-G-J [2]
            file-B-G-K [16]
            link-B-G-L ---> /folder-A // [folder-A]
                file-A-R [64]
                file-A-S [8]
                file-A-T [128]
        file-B-M [32]
    link-Z ---> /folder-A/file-A-S // file-A-S [8]
)");
	}
}

TEST(Folder, Operations)
{
	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(data::json_str));

	std::unique_ptr<tree::Folder> ptr { tree::ParseDisk(json) };
	EXPECT_NE(ptr.get(), nullptr);

	EXPECT_EQ(ptr->Content().size(), 5);

	EXPECT_EQ(ptr->Find("/fds"), nullptr);
	EXPECT_EQ(ptr->Find("/folder-A/fdsdf"), nullptr);

	auto node = ptr->Find("/file-X");
	EXPECT_NE(node, nullptr);

	ptr->Remove(node);
	EXPECT_EQ(ptr->Find("/file-X"), nullptr);

	ptr->Insert(node);
	EXPECT_NE(ptr->Find("/file-X"), nullptr);
}
