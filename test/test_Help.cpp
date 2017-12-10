#include "gtest/gtest.h"

#include "../cmd_Handler.h"

#include <sstream>

TEST(Help, Command)
{
	auto command = cmd::GetHandler("help");
	EXPECT_NE(command, nullptr);

	std::stringstream str;

	EXPECT_TRUE(command(nullptr, str));
	EXPECT_FALSE(str.str().empty());

	auto Quit = cmd::GetHandler("help quit");
	EXPECT_NE(Quit, nullptr);
	EXPECT_TRUE(Quit(nullptr, str));
	EXPECT_FALSE(str.str().empty());

	auto List = cmd::GetHandler("help list");
	EXPECT_NE(List, nullptr);
	EXPECT_TRUE(List(nullptr, str));
	EXPECT_FALSE(str.str().empty());

	auto Size= cmd::GetHandler("help size");
	EXPECT_NE(Size, nullptr);
	EXPECT_TRUE(Size(nullptr, str));
	EXPECT_FALSE(str.str().empty());

	auto Dump = cmd::GetHandler("help dump");
	EXPECT_NE(Dump, nullptr);
	EXPECT_TRUE(Dump(nullptr, str));
	EXPECT_FALSE(str.str().empty());

	auto RM = cmd::GetHandler("help rm");
	EXPECT_NE(RM, nullptr);
	EXPECT_TRUE(RM(nullptr, str));
	EXPECT_FALSE(str.str().empty());

	auto MKDIR = cmd::GetHandler("help mkdir");
	EXPECT_NE(MKDIR, nullptr);
	EXPECT_TRUE(MKDIR(nullptr, str));
	EXPECT_FALSE(str.str().empty());
	
	auto Link = cmd::GetHandler("help link");
	EXPECT_NE(Link, nullptr);
	EXPECT_TRUE(Link(nullptr, str));
	EXPECT_FALSE(str.str().empty());

	auto Touch = cmd::GetHandler("help touch");
	EXPECT_NE(Touch, nullptr);
	EXPECT_TRUE(Touch(nullptr, str));
	EXPECT_FALSE(str.str().empty());
}
