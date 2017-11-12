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

		std::unique_ptr<tree::Node> ptr { tree::Node::Parse(json) };
		EXPECT_NE(dynamic_cast<tree::Folder*>(ptr.get()), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name":"link", "link": ""})"));

		std::unique_ptr<tree::Node> ptr { tree::Node::Parse(json) };
		EXPECT_NE(dynamic_cast<tree::Link*>(ptr.get()), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name":"file", "size": "1"})"));

		std::unique_ptr<tree::Node> ptr { tree::Node::Parse(json) };
		EXPECT_NE(dynamic_cast<tree::File*>(ptr.get()), nullptr);
	}
}

TEST(Node, Failed)
{
	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"name":"folder"})"));

		std::unique_ptr<tree::Node> ptr { tree::Node::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"content": []})"));

		std::unique_ptr<tree::Node> ptr { tree::Node::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"link": ""})"));

		std::unique_ptr<tree::Node> ptr { tree::Node::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(R"({"size": ""})"));

		std::unique_ptr<tree::Node> ptr { tree::Node::Parse(json) };
		EXPECT_EQ(ptr.get(), nullptr);
	}
}
