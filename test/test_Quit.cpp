#include "gtest/gtest.h"

#include "../cmd_Handler.h"

#include <sstream>

TEST(Quit, Command)
{
	auto command = cmd::GetHandler("quit");
	EXPECT_NE(command, nullptr);

	std::stringstream str;

	EXPECT_FALSE(command(nullptr, str));
	EXPECT_FALSE(str.str().empty());
}
