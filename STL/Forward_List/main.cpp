#include <gtest/gtest.h>
#include "Forward_List.hpp"

template<typename T>
std::vector<T> to_vector(const Forward_List<T>& list) {
	std::vector<T> result;
	for (const auto& x : list)
		result.push_back(x);
	return result;
}

TEST(ForwardList, InitializerList) {
	Forward_List<int> list = {1, 2, 3};

	EXPECT_EQ(list.size(), 3);
	EXPECT_TRUE(list.search(1));
	EXPECT_TRUE(list.search(3));
}

TEST(ForwardList, PushFront) {
	Forward_List<int> list;

	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	EXPECT_EQ(to_vector(list), std::vector<int>({3,2,1}));
}

TEST(ForwardList, PushBack) {
	Forward_List<int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	EXPECT_EQ(to_vector(list), std::vector<int>({1,2,3}));
}

TEST(ForwardList, PopFront) {
	Forward_List<int> list = {1,2,3};

	list.pop_front();

	EXPECT_EQ(to_vector(list), std::vector<int>({2,3}));
}

TEST(ForwardList, PopBack) {
	Forward_List<int> list = {1,2,3};

	list.pop_back();

	EXPECT_EQ(to_vector(list), std::vector<int>({1,2}));
}

TEST(ForwardList, PopSingleElement) {
	Forward_List<int> list = {42};

	list.pop_back();

	EXPECT_EQ(list.size(), 0);
}

TEST(ForwardList, InsertAfter) {
	Forward_List<int> list = {1,2,4};

	auto it = list.find(2);
	list.insert_after(it, 3);

	EXPECT_EQ(to_vector(list), std::vector<int>({1,2,3,4}));
}

TEST(ForwardList, Find) {
	Forward_List<int> list = {10,20,30};

	auto it = list.find(20);

	ASSERT_NE(it, list.end());
	EXPECT_EQ(*it, 20);
}

TEST(ForwardList, FindNotFound) {
	Forward_List<int> list = {1,2,3};

	auto it = list.find(100);

	EXPECT_EQ(it, list.end());
}

TEST(ForwardList, Search) {
	Forward_List<int> list = {1,2,3};

	EXPECT_TRUE(list.search(2));
	EXPECT_FALSE(list.search(99));
}

TEST(ForwardList, IteratorTraversal) {
	Forward_List<int> list = {1,2,3};

	std::vector<int> result;
	for (auto it = list.begin(); it != list.end(); ++it)
		result.push_back(*it);

	EXPECT_EQ(result, std::vector<int>({1,2,3}));
}

TEST(ForwardList, RangeBasedFor) {
	Forward_List<int> list = {5,6,7};

	std::vector<int> result;
	for (int x : list)
		result.push_back(x);

	EXPECT_EQ(result, std::vector<int>({5,6,7}));
}

TEST(ForwardList, CopyConstructor) {
	Forward_List<int> list = {1,2,3};
	Forward_List<int> copy = list;

	EXPECT_EQ(to_vector(copy), std::vector<int>({1,2,3}));
}

TEST(ForwardList, CopyAssignment) {
	Forward_List<int> list1 = {1,2,3};
	Forward_List<int> list2;

	list2 = list1;

	EXPECT_EQ(to_vector(list2), std::vector<int>({1,2,3}));
}


TEST(ForwardList, Clear) {
	Forward_List<int> list = {1,2,3};

	list.clear();

	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(list.begin(), list.end());
}

TEST(ForwardList, EmptyOperations) {
	Forward_List<int> list;

	list.pop_front();
	list.pop_back();

	EXPECT_EQ(list.size(), 0);
}

TEST(ForwardList, InsertAfterNull) {
	Forward_List<int> list = {1,2};

	list.insert_after(list.end(), 5);

	EXPECT_EQ(to_vector(list), std::vector<int>({1,2}));
}

TEST(ForwardList, LargeInsertions) {
	Forward_List<int> list;

	for (int i = 0; i < 1000; ++i)
		list.push_back(i);

	EXPECT_EQ(list.size(), 1000);
	EXPECT_TRUE(list.search(999));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
