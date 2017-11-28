#include "gtest/gtest.h"

#include "rapidjson/document.h"

#include "../tree_Disk.h"

#include <memory>
#include <sstream>

#include "data.h"

TEST(Disk, Parse)
{
	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse("[]"));
		//zmenit vsetky unique na auto vo vsetkych testoch
		//std::unique_ptr<tree::Folder> ptr { tree::ParseDisk(json) };
		auto ptr{ tree::ParseDisk(json) };
		EXPECT_NE(ptr.get(), nullptr);

		{
			std::stringstream str;
			ptr->List(false, false, "", str);

			EXPECT_STREQ(str.str().c_str(), "[]\n");
		}

	}

	{
		rapidjson::Document json;
		EXPECT_TRUE((rapidjson::ParseResult)json.Parse(data::json_str));

		auto ptr { tree::ParseDisk(json) };
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
	}
}
