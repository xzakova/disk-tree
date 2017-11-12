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
}
