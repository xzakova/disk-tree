#include "gtest/gtest.h"

#include "../cmd_Handler.h"
#include "../tree_Disk.h"

#include <memory>
#include <sstream>

#include "data.h"

TEST(Size, Command)
{
	{
		auto command = cmd::GetHandler("size -faddsdfs");
		EXPECT_EQ(command, nullptr);
	}

	{
		auto command = cmd::GetHandler("size -recursive -faddsdfs");
		EXPECT_EQ(command, nullptr);
	}
 
	{
		auto command = cmd::GetHandler("size -recursive -follow -faddsdfs");
		EXPECT_EQ(command, nullptr);
	}

	{
		auto command = cmd::GetHandler("size faddsdfs");
		EXPECT_EQ(command, nullptr);
	}

	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(data::json_str));

	std::unique_ptr<tree::Folder> ptr { tree::ParseDisk(json) };
	EXPECT_NE(ptr.get(), nullptr);

	{
		auto command = cmd::GetHandler("size");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    4\n");
	}

	{
		auto command = cmd::GetHandler("size -follow");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    44\n");
	}

	{
		auto command = cmd::GetHandler("size -recursive");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    254\n");
	}

	{
		auto command = cmd::GetHandler("size -follow -recursive");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    712\n");
	}

	{
		auto command = cmd::GetHandler("size -recursive -follow");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    712\n");
	}

	{
		auto command = cmd::GetHandler("size /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    32\n");
	}

	{
		auto command = cmd::GetHandler("size -follow /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    32\n");
	}

	{
		auto command = cmd::GetHandler("size -recursive /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    50\n");
	}

	{
		auto command = cmd::GetHandler("size -follow -recursive /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    250\n");
	}

	{
		auto command = cmd::GetHandler("size -recursive -follow /folder-B");
		EXPECT_NE(command, nullptr);

		std::stringstream str;

		EXPECT_TRUE(command(ptr.get(), str));
		EXPECT_STREQ(str.str().c_str(), "    250\n");
	}
}
