#include "gtest/gtest.h"

#include "../tree_Size.h"

using namespace tree;

TEST(Size, Initialization_String_B)
{
	EXPECT_DOUBLE_EQ(Size("1234B"), 1234);

	EXPECT_DOUBLE_EQ(Size("13123"), 13123);

	EXPECT_DOUBLE_EQ(Size(908), 908);
}

TEST(Size, Initialization_String_kB)
{
	EXPECT_DOUBLE_EQ(Size("12kB"), 12 * 1024);

	EXPECT_DOUBLE_EQ(Size("45.54kB"), 45.54 * 1024);

	EXPECT_DOUBLE_EQ(Size(".356kB"), .356 * 1024);

	EXPECT_DOUBLE_EQ(Size("0.36kB"), .360 * 1024);
}

TEST(Size, Initialization_String_MB)
{
	EXPECT_DOUBLE_EQ(Size("435MB"), 435 * 1024 * 1024);

	EXPECT_DOUBLE_EQ(Size("9.65MB"), 9.65 * 1024 * 1024);

	EXPECT_DOUBLE_EQ(Size(".876MB"), .876 * 1024 * 1024);

	EXPECT_DOUBLE_EQ(Size("0.435MB"), .435 * 1024 * 1024);
}

TEST(Size, Initialization_String_GB)
{
	EXPECT_DOUBLE_EQ(Size("78GB"), 78. * 1024 *1024 * 1024);

	EXPECT_DOUBLE_EQ(Size("4.36GB"), 4.36 * 1024 * 1024 * 1024);

	EXPECT_DOUBLE_EQ(Size(".645GB"), .645 * 1024 * 1024 * 1024);

	EXPECT_DOUBLE_EQ(Size("0.328GB"), .328 * 1024 * 1024 * 1024);
}

TEST(Size, Initialization_Failed)
{
	EXPECT_LT((double)Size("-9B"), 0.);

	EXPECT_LT((double)Size("9b"), 0.);

	EXPECT_LT((double)Size("23mb"), 0.);

	EXPECT_LT((double)Size("65gb"), 0.);

	EXPECT_LT((double)Size("0,234GB"), 0.);
}

TEST(Size, ToString)
{
	EXPECT_STREQ(Size("9B").toString().c_str(), "9");

	EXPECT_STREQ(Size("9MB").toString().c_str(), "9MB");

	EXPECT_STREQ(Size("2048MB").toString().c_str(), "2GB");

	EXPECT_STREQ(Size("2132145").toString().c_str(), "2.033MB");
}
