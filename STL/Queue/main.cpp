#include <gtest/gtest.h>
#include "Queue.hpp"

TEST(QueueTest, InitiallyEmpty) {
	Queue<int> q;
	EXPECT_TRUE(q.empty());
	EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, PushAndFront) {
	Queue<int> q;
	q.push(10);
	q.push(20);

	EXPECT_EQ(q.front(), 10);
	EXPECT_EQ(q.back(), 20);
}

TEST(QueueTest, FIFOOrder) {
	Queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);

	EXPECT_EQ(q.front(), 1);
	q.pop();
	EXPECT_EQ(q.front(), 2);
	q.pop();
	EXPECT_EQ(q.front(), 3);
}

TEST(QueueTest, PopReducesSize) {
	Queue<int> q;

	q.push(1);
	q.push(2);

	q.pop();
	EXPECT_EQ(q.size(), 1);

	q.pop();
	EXPECT_TRUE(q.empty());
}

TEST(QueueTest, PopOnEmptyThrows) {
	Queue<int> q;
	EXPECT_THROW(q.pop(), std::runtime_error);
}

TEST(QueueTest, FrontOnEmptyThrows) {
	Queue<int> q;
	EXPECT_THROW(q.front(), std::runtime_error);
}

TEST(QueueTest, BackOnEmptyThrows) {
	Queue<int> q;
	EXPECT_THROW(q.back(), std::runtime_error);
}

TEST(QueueTest, WrapAroundBehavior) {
	Queue<int> q(4);

	q.push(1);
	q.push(2);
	q.push(3);

	q.pop();
	q.pop();

	q.push(4);
	q.push(5);

	EXPECT_EQ(q.front(), 3);
	EXPECT_EQ(q.back(), 5);

	q.pop();
	EXPECT_EQ(q.front(), 4);
}

TEST(QueueTest, GrowWorks) {
	Queue<int> q(2);

	for (int i = 0; i < 100; ++i)
		q.push(i);

	EXPECT_EQ(q.front(), 0);
	EXPECT_EQ(q.back(), 99);

	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(q.front(), i);
		q.pop();
	}

	EXPECT_TRUE(q.empty());
}

TEST(QueueTest, ClearWorks) {
	Queue<int> q;

	for (int i = 0; i < 10; ++i)
		q.push(i);

	q.clear();

	EXPECT_TRUE(q.empty());
	EXPECT_EQ(q.size(), 0);

	q.push(42);
	EXPECT_EQ(q.front(), 42);
}

TEST(QueueTest, InterleavedOperations) {
	Queue<int> q;

	q.push(1);
	q.push(2);
	q.pop();
	q.push(3);
	q.pop();
	q.push(4);

	EXPECT_EQ(q.front(), 3);
	EXPECT_EQ(q.back(), 4);
}

int main(int ac, char **av) {
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
