#include <gtest/gtest.h>
#include "PriorityQueue.hpp"

TEST(PriorityQueueTest, EmptyOnInit) {
	PriorityQueue<int> pq;
	EXPECT_TRUE(pq.empty());
	EXPECT_EQ(pq.size(), 0);
}

TEST(PriorityQueueTest, PushAndTop) {
	PriorityQueue<int> pq;
	pq.push(10);
	pq.push(5);
	pq.push(20);

	EXPECT_EQ(pq.top(), 20);
}

TEST(PriorityQueueTest, PushPopOrder) {
	PriorityQueue<int> pq;

	pq.push(10);
	pq.push(5);
	pq.push(20);
	pq.push(15);

	EXPECT_EQ(pq.top(), 20);
	pq.pop();

	EXPECT_EQ(pq.top(), 15);
	pq.pop();

	EXPECT_EQ(pq.top(), 10);
	pq.pop();

	EXPECT_EQ(pq.top(), 5);
}

TEST(PriorityQueueTest, SizeAfterOperations) {
	PriorityQueue<int> pq;

	pq.push(1);
	pq.push(2);
	pq.push(3);

	EXPECT_EQ(pq.size(), 3);

	pq.pop();
	EXPECT_EQ(pq.size(), 2);
}

TEST(PriorityQueueTest, TopThrowsOnEmpty) {
	PriorityQueue<int> pq;
	EXPECT_THROW(pq.top(), std::out_of_range);
}

TEST(PriorityQueueTest, PopThrowsOnEmpty) {
	PriorityQueue<int> pq;
	EXPECT_THROW(pq.pop(), std::out_of_range);
}

TEST(PriorityQueueTest, SingleElement) {
	PriorityQueue<int> pq;

	pq.push(42);
	EXPECT_EQ(pq.top(), 42);

	pq.pop();
	EXPECT_TRUE(pq.empty());
}


TEST(PriorityQueueTest, ManyElements) {
	PriorityQueue<int> pq;

	for (int i = 0; i < 1000; ++i)
		pq.push(i);

	for (int i = 999; i >= 0; --i) {
		EXPECT_EQ(pq.top(), i);
		pq.pop();
	}
}

TEST(PriorityQueueTest, MinHeapBehavior) {
	PriorityQueue<int, std::greater<int>> pq;

	pq.push(10);
	pq.push(5);
	pq.push(20);

	EXPECT_EQ(pq.top(), 5);

	pq.pop();
	EXPECT_EQ(pq.top(), 10);
}

TEST(PriorityQueueTest, HandlesDuplicates) {
	PriorityQueue<int> pq;

	pq.push(10);
	pq.push(10);
	pq.push(10);

	EXPECT_EQ(pq.top(), 10);

	pq.pop();
	EXPECT_EQ(pq.top(), 10);
}

TEST(PriorityQueueTest, NegativeNumbers) {
	PriorityQueue<int> pq;

	pq.push(-10);
	pq.push(-5);
	pq.push(-20);

	EXPECT_EQ(pq.top(), -5);
}
