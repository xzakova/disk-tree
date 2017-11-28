#include "gtest/gtest.h"

#include "../cmd_Handler.h"
#include "../tree_Disk.h"

#include <memory>
#include <sstream>

#include "data.h"

TEST(List, Command)
{
	{
		auto command = cmd::GetHandler("list -faddsdfs");
		EXPECT_EQ(command, nullptr);
	}

	{
		auto command = cmd::GetHandler("list -recursive -faddsdfs");
		EXPECT_EQ(command, nullptr);
	}

	{
		auto command = cmd::GetHandler("list -recursive -follow -faddsdfs");
		EXPECT_EQ(command, nullptr);
	}

	{
		auto command = cmd::GetHandler("list faddsdfs");
		EXPECT_EQ(command, nullptr);
	}

	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(data::json_str));

	auto ptr { tree::ParseDisk(json) };
	EXPECT_NE(ptr.get(), nullptr);

	{
		auto command = cmd::GetHandler("list");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), R"([]
    [folder-A]
    [folder-B]
    file-X [4]
    link-Y ---> /folder-B
    link-Z ---> /folder-A/file-A-S
)");
	}

	{
		auto command = cmd::GetHandler("list -follow");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
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
		auto command = cmd::GetHandler("list -recursive");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
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
		auto command = cmd::GetHandler("list -follow -recursive");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
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

	{
		auto command = cmd::GetHandler("list -recursive -follow");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
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

	{
		auto command = cmd::GetHandler("list /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "[folder-B]\n    [folder-B-G]\n    file-B-M [32]\n");
	}

	{
		auto command = cmd::GetHandler("list -follow /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "[folder-B]\n    [folder-B-G]\n    file-B-M [32]\n");
	}

	{
		auto command = cmd::GetHandler("list -recursive /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), R"([folder-B]
    [folder-B-G]
        file-B-G-J [2]
        file-B-G-K [16]
        link-B-G-L ---> /folder-A
    file-B-M [32]
)");
	}

	{
		auto command = cmd::GetHandler("list -follow -recursive /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), R"([folder-B]
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

	{
		auto command = cmd::GetHandler("list -recursive -follow /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), R"([folder-B]
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
}
