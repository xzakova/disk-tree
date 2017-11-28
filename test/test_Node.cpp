#include "gtest/gtest.h"

#include "rapidjson/document.h"

#include "../tree_File.h"
#include "../tree_Link.h"
#include "../tree_Folder.h"

#include <memory>

TEST(Node, Parse)
{
	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name":"folder", "content": []})"));

		auto ptr { tree::Node::Parse(json) };
		EXPECT_NE(dynamic_cast<tree::Folder*>(ptr.get()), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name":"link", "link": ""})"));

		auto ptr { tree::Node::Parse(json) };
		EXPECT_NE(dynamic_cast<tree::Link*>(ptr.get()), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name":"file", "size": "1"})"));

		auto ptr { tree::Node::Parse(json) };
		EXPECT_NE(dynamic_cast<tree::File*>(ptr.get()), nullptr);
	}
}

TEST(Node, Failed)
{
	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name":"folder"})"));

		auto ptr { tree::Node::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"content": []})"));

		auto ptr { tree::Node::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"link": ""})"));

		auto ptr { tree::Node::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"size": ""})"));

		auto ptr { tree::Node::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}
}
