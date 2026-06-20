#include <gtest/gtest.h>
#include "Circular_List.hpp"

TEST(CircularList, InitiallyEmpty) {
	Circular_List<int> cl;

	EXPECT_TRUE(cl.empty());
	EXPECT_EQ(cl.size(), 0);
}

TEST(CircularList, PushBackSingle) {
	Circular_List<int> cl;

	cl.push_back(10);

	EXPECT_EQ(cl.front(), 10);
	EXPECT_EQ(cl.back(), 10);
	EXPECT_EQ(cl.size(), 1);
}

TEST(CircularList, PushBackMultiple) {
	Circular_List<int> cl;

	cl.push_back(1);
	cl.push_back(2);
	cl.push_back(3);

	EXPECT_EQ(cl.front(), 1);
	EXPECT_EQ(cl.back(), 3);
	EXPECT_EQ(cl.size(), 3);
}

TEST(CircularList, PushFrontSingle) {
	Circular_List<int> cl;

	cl.push_front(99);

	EXPECT_EQ(cl.front(), 99);
	EXPECT_EQ(cl.back(), 99);
	EXPECT_EQ(cl.size(), 1);
}

TEST(CircularList, PushFrontMultiple) {
	Circular_List<int> cl;

	cl.push_front(1);
	cl.push_front(2);
	cl.push_front(3);

	EXPECT_EQ(cl.front(), 3);
	EXPECT_EQ(cl.back(), 1);
	EXPECT_EQ(cl.size(), 3);
}


TEST(CircularList, PopFrontSingle) {
	Circular_List<int> cl;

	cl.push_back(42);
	cl.pop_front();

	EXPECT_TRUE(cl.empty());
	EXPECT_EQ(cl.size(), 0);
}

TEST(CircularList, PopFrontMultiple) {
	Circular_List<int> cl;

	cl.push_back(1);
	cl.push_back(2);
	cl.push_back(3);

	cl.pop_front();

	EXPECT_EQ(cl.front(), 2);
	EXPECT_EQ(cl.back(), 3);
	EXPECT_EQ(cl.size(), 2);
}


TEST(CircularList, PopBackSingle) {
	Circular_List<int> cl;

	cl.push_back(55);
	cl.pop_back();

	EXPECT_TRUE(cl.empty());
}

TEST(CircularList, PopBackMultiple) {
	Circular_List<int> cl;

	cl.push_back(1);
	cl.push_back(2);
	cl.push_back(3);

	cl.pop_back();

	EXPECT_EQ(cl.front(), 1);
	EXPECT_EQ(cl.back(), 2);
	EXPECT_EQ(cl.size(), 2);
}


TEST(CircularList, MixedOperations) {
	Circular_List<int> cl;

	cl.push_back(2);
	cl.push_front(1);
	cl.push_back(3);
	cl.push_front(0);

	EXPECT_EQ(cl.front(), 0);
	EXPECT_EQ(cl.back(), 3);
	EXPECT_EQ(cl.size(), 4);

	cl.pop_front();
	EXPECT_EQ(cl.front(), 1);

	cl.pop_back();
	EXPECT_EQ(cl.back(), 2);
}


TEST(CircularList, CopyConstructor) {
	Circular_List<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	Circular_List<int> b = a;

	EXPECT_EQ(b.size(), 3);
	EXPECT_EQ(b.front(), 1);
	EXPECT_EQ(b.back(), 3);
}


TEST(CircularList, CopyAssignment) {
	Circular_List<int> a;
	a.push_back(1);
	a.push_back(2);

	Circular_List<int> b;
	b.push_back(99);

	b = a;

	EXPECT_EQ(b.size(), 2);
	EXPECT_EQ(b.front(), 1);
	EXPECT_EQ(b.back(), 2);
}


TEST(CircularList, MoveConstructor) {
	Circular_List<int> a;

	a.push_back(10);
	a.push_back(20);

	Circular_List<int> b = std::move(a);

	EXPECT_EQ(b.size(), 2);
	EXPECT_EQ(b.front(), 10);
	EXPECT_EQ(b.back(), 20);

	EXPECT_TRUE(a.empty());
}

TEST(CircularList, MoveAssignment) {
	Circular_List<int> a;
	a.push_back(1);
	a.push_back(2);

	Circular_List<int> b;
	b.push_back(100);

	b = std::move(a);

	EXPECT_EQ(b.size(), 2);
	EXPECT_EQ(b.front(), 1);
	EXPECT_EQ(b.back(), 2);

	EXPECT_TRUE(a.empty());
}


TEST(CircularList, MultiplePopsToEmpty) {
	Circular_List<int> cl;

	cl.push_back(1);
	cl.push_back(2);

	cl.pop_front();
	cl.pop_back();

	EXPECT_TRUE(cl.empty());
	EXPECT_EQ(cl.size(), 0);
}

TEST(CircularList, StressTest) {
	Circular_List<int> cl;

	for (int i = 0; i < 1000; i++) {
		cl.push_back(i);
	}

	EXPECT_EQ(cl.size(), 1000);
	EXPECT_EQ(cl.front(), 0);
	EXPECT_EQ(cl.back(), 999);

	for (int i = 0; i < 1000; i++) {
		cl.pop_front();
	}

	EXPECT_TRUE(cl.empty());
}

int main(int ac, char **av) {
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
