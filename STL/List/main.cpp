#include <gtest/gtest.h>
#include "List.hpp"

TEST(ListTest, PushBack) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.size(), 3);

	auto it = l.begin();
	EXPECT_EQ(*it++, 1);
	EXPECT_EQ(*it++, 2);
	EXPECT_EQ(*it++, 3);
}

TEST(ListTest, PushFront) {
	List<int> l;
	l.push_front(3);
	l.push_front(2);
	l.push_front(1);

	auto it = l.begin();
	EXPECT_EQ(*it++, 1);
	EXPECT_EQ(*it++, 2);
	EXPECT_EQ(*it++, 3);
}

TEST(ListTest, PopBack) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.pop_back();
	EXPECT_EQ(l.size(), 2);

	auto it = l.begin();
	EXPECT_EQ(*it++, 1);
	EXPECT_EQ(*it++, 2);
}

TEST(ListTest, PopFront) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.pop_front();
	EXPECT_EQ(l.size(), 2);

	auto it = l.begin();
	EXPECT_EQ(*it++, 2);
	EXPECT_EQ(*it++, 3);
}

TEST(ListTest, Empty) {
	List<int> l;
	EXPECT_TRUE(l.empty());

	l.push_back(1);
	EXPECT_FALSE(l.empty());
}

TEST(ListTest, IteratorTraversal) {
	List<int> l{1, 2, 3, 4, 5};

	int expected = 1;
	for (auto it = l.begin(); it != l.end(); ++it) {
		EXPECT_EQ(*it, expected++);
	}

	EXPECT_EQ(expected, 6);
}

TEST(ListTest, CopyConstructor) {
	List<int> l1;
	l1.push_back(10);
	l1.push_back(20);
	l1.push_back(30);

	List<int> l2 = l1;

	EXPECT_EQ(l2.size(), 3);

	auto it = l2.begin();
	EXPECT_EQ(*it++, 10);
	EXPECT_EQ(*it++, 20);
	EXPECT_EQ(*it++, 30);
}

TEST(ListTest, CopyAssignment) {
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);

	List<int> l2;
	l2.push_back(100);

	l2 = l1;

	EXPECT_EQ(l2.size(), 2);

	auto it = l2.begin();
	EXPECT_EQ(*it++, 1);
	EXPECT_EQ(*it++, 2);
}

TEST(ListTest, MoveConstructor) {
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);

	List<int> l2 = std::move(l1);

	EXPECT_EQ(l2.size(), 2);
	EXPECT_TRUE(l1.empty());
}

TEST(ListTest, MoveAssignment) {
	List<int> l1;
	l1.push_back(1);
	l1.push_back(2);

	List<int> l2;
	l2 = std::move(l1);

	EXPECT_EQ(l2.size(), 2);
	EXPECT_TRUE(l1.empty());
}

TEST(ListTest, ConstIteration) {
	List<int> l{5, 10, 15};

	const List<int>& cl = l;

	auto it = cl.begin();
	EXPECT_EQ(*it++, 5);
	EXPECT_EQ(*it++, 10);
	EXPECT_EQ(*it++, 15);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
