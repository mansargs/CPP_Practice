#include "CTAD.hpp"
// #include <type_traits>
#include <gtest/gtest.h>
#include <string>

TEST(Pair, Construct_Int_Double)
{
	Pair p(1, 2.0);

	EXPECT_EQ(p.first, 1);
	EXPECT_DOUBLE_EQ(p.second, 2.0);
}

TEST(Pair, Construct_CString_StdString)
{
	Pair p("hello", std::string("world"));

	EXPECT_STREQ(p.first, "hello");
	EXPECT_EQ(p.second, "world");
}

TEST(Pair, Access_First_And_Second_Values)
{
	Pair p(42, std::string("answer"));

	EXPECT_EQ(p.first, 42);
	EXPECT_EQ(p.second, "answer");
}

TEST(Pair, Copy_Construction_Works)
{
	Pair p1(10, 3.14);
	Pair p2 = p1;

	EXPECT_EQ(p2.first, 10);
	EXPECT_DOUBLE_EQ(p2.second, 3.14);
}

TEST(Pair, Copy_Assignment_Works)
{
	Pair p1(5, 1.23);
	Pair p2(0, 0.0);

	p2 = p1;

	EXPECT_EQ(p2.first, 5);
	EXPECT_DOUBLE_EQ(p2.second, 1.23);
}

TEST(Pair, CTAD_Deduction_Int_Double)
{
	auto p = Pair(1, 2.0);

	using Expected = Pair<int, double>;
	static_assert(std::is_same_v<decltype(p), Expected>);
}

TEST(Pair, Const_Pair_Still_Readable)
{
	const Pair p(7, std::string("const"));

	EXPECT_EQ(p.first, 7);
	EXPECT_EQ(p.second, "const");
}

TEST(Pair, Swap_Pairs_Works)
{
	Pair a(1, std::string("A"));
	Pair b(2, std::string("B"));

	std::swap(a, b);

	EXPECT_EQ(a.first, 2);
	EXPECT_EQ(a.second, "B");

	EXPECT_EQ(b.first, 1);
	EXPECT_EQ(b.second, "A");
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
