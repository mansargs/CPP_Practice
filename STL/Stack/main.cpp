#include <gtest/gtest.h>
#include "Stack.hpp"

TEST(StackTest, PushTopPopBasic) {
	Stack<int> st;

	st.push(10);
	st.push(20);
	st.push(30);

	EXPECT_EQ(st.top(), 30);
	st.pop();
	EXPECT_EQ(st.top(), 20);

	st.pop();
	EXPECT_EQ(st.top(), 10);
}

TEST(StackTest, EmptyCheck) {
	Stack<int> st;

	EXPECT_TRUE(st.empty());

	st.push(1);
	EXPECT_FALSE(st.empty());
}

TEST(StackTest, PopThrowsOnEmpty) {
	Stack<int> st;

	EXPECT_THROW(st.pop(), std::runtime_error);
}

TEST(StackTest, TopThrowsOnEmpty) {
	Stack<int> st;

	EXPECT_THROW(st.top(), std::runtime_error);
}

TEST(StackTest, GrowWorks) {
	Stack<int> st(2);

	for (int i = 0; i < 100; ++i)
		st.push(i);

	EXPECT_EQ(st.top(), 99);

	for (int i = 99; i >= 0; --i) {
		EXPECT_EQ(st.top(), i);
		st.pop();
	}

	EXPECT_TRUE(st.empty());
}

TEST(StackTest, CopyConstructor) {
	Stack<int> st;
	st.push(1);
	st.push(2);

	Stack<int> copy(st);

	EXPECT_EQ(copy.top(), 2);
	copy.pop();
	EXPECT_EQ(copy.top(), 1);
}

TEST(StackTest, MoveConstructor) {
	Stack<int> st;
	st.push(5);
	st.push(10);

	Stack<int> moved(std::move(st));

	EXPECT_EQ(moved.top(), 10);
	EXPECT_TRUE(st.empty());
}

TEST(StackTest, AssignmentOperator) {
	Stack<int> a;
	a.push(1);
	a.push(2);

	Stack<int> b;
	b = a;

	EXPECT_EQ(b.top(), 2);
	b.pop();
	EXPECT_EQ(b.top(), 1);
}


int main(int ac, char **av) {
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
