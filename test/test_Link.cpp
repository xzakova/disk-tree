#include "gtest/gtest.h"

#include "rapidjson/document.h"

#include "../tree_Link.h"
#include "../tree_Folder.h"
#include "../tree_Disk.h"

#include <memory>
#include <sstream>

#include "data.h"

TEST(Link, Initialization)
{
	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name": "link"})"));

		std::unique_ptr<tree::Link> ptr { tree::Link::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"link": ""})"));

		std::unique_ptr<tree::Link> ptr { tree::Link::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name": "link", "link": ""})"));

		std::unique_ptr<tree::Link> ptr { tree::Link::Parse(json) };
		EXPECT_NE(ptr.get(), nullptr);
	}
}

TEST(Link, Size)
{
	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(data::json_str));

	std::unique_ptr<tree::Folder> folder { tree::ParseDisk(json) };
	EXPECT_NE(folder.get(), nullptr);

	auto link = dynamic_cast<tree::Link*>(folder->Find("/link-Z"));
	EXPECT_NE(link, nullptr);

	EXPECT_DOUBLE_EQ((double)link->Size(false, false), 0);

	EXPECT_DOUBLE_EQ((double)link->Size(true, false), 8);

	EXPECT_DOUBLE_EQ((double)link->Size(false, true), 0);

	EXPECT_DOUBLE_EQ((double)link->Size(true, true), 8);

	link = dynamic_cast<tree::Link*>(folder->Find("/link-Y"));
	EXPECT_NE(link, nullptr);

	EXPECT_DOUBLE_EQ((double)link->Size(false, false), 0);

	EXPECT_DOUBLE_EQ((double)link->Size(true, false), 32);

	EXPECT_DOUBLE_EQ((double)link->Size(false, true), 0);

	EXPECT_DOUBLE_EQ((double)link->Size(true, true), (2 + 16 + (64 + 8 + 128)) + 32);
}

TEST(Link, List)
{
	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(data::json_str));

	std::unique_ptr<tree::Folder> folder { tree::ParseDisk(json) };
	EXPECT_NE(folder.get(), nullptr);

	auto link = dynamic_cast<tree::Link*>(folder->Find("/link-Z"));
	EXPECT_NE(link, nullptr);

	{
		std::stringstream str;
		link->List(false, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Z ---> /folder-A/file-A-S\n");
	}

	{
		std::stringstream str;
		link->List(true, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Z ---> /folder-A/file-A-S // file-A-S [8]\n");
	}

	{
		std::stringstream str;
		link->List(false, true, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Z ---> /folder-A/file-A-S\n");
	}

	{
		std::stringstream str;
		link->List(true, true, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Z ---> /folder-A/file-A-S // file-A-S [8]\n");
	}

	link->Set(nullptr);
	{
		std::stringstream str;
		link->List(false, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Z -X-> /folder-A/file-A-S\n");
	}

	{
		std::stringstream str;
		link->List(true, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Z -X-> /folder-A/file-A-S\n");
	}

	{
		std::stringstream str;
		link->List(false, true, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Z -X-> /folder-A/file-A-S\n");
	}

	{
		std::stringstream str;
		link->List(true, true, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Z -X-> /folder-A/file-A-S\n");
	}

	link = dynamic_cast<tree::Link*>(folder->Find("/link-Y"));
	EXPECT_NE(link, nullptr);

	{
		std::stringstream str;
		link->List(false, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Y ---> /folder-B\n");
	}

	{
		std::stringstream str;
		link->List(true, false, "", str);
		EXPECT_STREQ(str.str().c_str(), R"(link-Y ---> /folder-B // [folder-B]
    [folder-B-G]
    file-B-M [32]
)");
	}

	{
		std::stringstream str;
		link->List(false, true, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Y ---> /folder-B\n");
	}

	{
		std::stringstream str;
		link->List(true, true, "", str);
		EXPECT_STREQ(str.str().c_str(), R"(link-Y ---> /folder-B // [folder-B]
    [folder-B-G]
        file-B-G-J [2]
        file-B-G-K [16]
        link-B-G-L ---> /folder-A // [folder-A]
            file-A-R [64]
            file-A-S [8]
            file-A-T [128]
    file-B-M [32]
)");
	}

	link->Set(nullptr);
	{
		std::stringstream str;
		link->List(false, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Y -X-> /folder-B\n");
	}

	{
		std::stringstream str;
		link->List(true, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Y -X-> /folder-B\n");
	}

	{
		std::stringstream str;
		link->List(false, true, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Y -X-> /folder-B\n");
	}

	{
		std::stringstream str;
		link->List(true, true, "", str);
		EXPECT_STREQ(str.str().c_str(), "link-Y -X-> /folder-B\n");
	}
}
