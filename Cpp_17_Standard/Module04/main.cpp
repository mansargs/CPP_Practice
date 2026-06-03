#include <gtest/gtest.h>
#include <tuple>
#include <string>
#include "FoldExpressions.hpp"

TEST(SumTest, Basic)
{
	EXPECT_EQ(sum(1,2,3), 6);
	EXPECT_EQ(sum(10,-3,7), 14);
}

TEST(ProductTest, Basic)
{
	EXPECT_EQ(product(2,3,4), 24);
	EXPECT_EQ(product(5,0,10), 0);
}

TEST(AllSameTypeTest, TrueCases)
{
	EXPECT_TRUE(all_same_type(1,2,3));
	EXPECT_TRUE(all_same_type(std::string("a"), std::string("b")));
}

TEST(AllSameTypeTest, FalseCases)
{
	EXPECT_FALSE(all_same_type(1,2.0,3));
}

TEST(ClampAllTest, Basic)
{
	auto t = clamp_all(1, 10, 5, -2, 20);

	auto [a, b, c] = t;

	EXPECT_EQ(a, 5);
	EXPECT_EQ(b, 1);
	EXPECT_EQ(c, 10);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
