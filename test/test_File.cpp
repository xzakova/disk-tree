#include "gtest/gtest.h"

#include "rapidjson/document.h"

#include "../tree_File.h"

#include <memory>

TEST(File, Initialization)
{
	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name": "file", "size": ""})"));

		std::unique_ptr<tree::File> ptr { tree::File::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"size": "1"})"));

		std::unique_ptr<tree::File> ptr { tree::File::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name": "file", "size": ".5kB"})"));

		std::unique_ptr<tree::File> ptr { tree::File::Parse(json) };
		EXPECT_NE(ptr.get(), nullptr);
	}
}

TEST(File, List)
{
	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name": "file", "size": ".5kB"})"));

	std::unique_ptr<tree::File> ptr { tree::File::Parse(json) };
	EXPECT_NE(ptr.get(), nullptr);

	{
		std::stringstream str;
		ptr->List(false, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "file [512]\n");
	}

	{
		std::stringstream str;
		ptr->List(false, true, "", str);
		EXPECT_STREQ(str.str().c_str(), "file [512]\n");
	}

	{
		std::stringstream str;
		ptr->List(true, false, "", str);
		EXPECT_STREQ(str.str().c_str(), "file [512]\n");
	}

	{
		std::stringstream str;
		ptr->List(true, true, "   ", str);
		EXPECT_STREQ(str.str().c_str(), "file [512]\n");
	}
}

TEST(File, Size)
{
	rapidjson::Document json;
	EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name": "file", "size": ".5kB"})"));

	std::unique_ptr<tree::File> ptr { tree::File::Parse(json) };
	EXPECT_NE(ptr.get(), nullptr);

	EXPECT_DOUBLE_EQ((double)ptr->Size(false, false), 512);

	EXPECT_DOUBLE_EQ((double)ptr->Size(false, true), 512);

	EXPECT_DOUBLE_EQ((double)ptr->Size(true, false), 512);

	EXPECT_DOUBLE_EQ((double)ptr->Size(true, true), 512);
}
