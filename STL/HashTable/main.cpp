#include <gtest/gtest.h>
#include "HashTable.hpp"

TEST(HashTable, InsertAndFind) {
    HashTable<int, std::string> ht;

    ht.insert(1, "one");
    ht.insert(2, "two");

    auto* v1 = ht.find(1);
    auto* v2 = ht.find(2);

    ASSERT_NE(v1, nullptr);
    ASSERT_NE(v2, nullptr);

    EXPECT_EQ(*v1, "one");
    EXPECT_EQ(*v2, "two");
}

TEST(HashTable, UpdateValue) {
    HashTable<int, std::string> ht;

    ht.insert(1, "one");
    ht.insert(1, "ONE_UPDATED");

    auto* v = ht.find(1);

    ASSERT_NE(v, nullptr);
    EXPECT_EQ(*v, "ONE_UPDATED");
}

TEST(HashTable, Erase) {
    HashTable<int, std::string> ht;

    ht.insert(1, "one");
    ht.insert(2, "two");

    EXPECT_TRUE(ht.erase(1));
    EXPECT_FALSE(ht.find(1));

    EXPECT_FALSE(ht.erase(100)); // not existing
}

TEST(HashTable, OperatorBracketInsert) {
    HashTable<int, std::string> ht;

    ht[1] = "one";
    ht[2] = "two";

    EXPECT_EQ(ht[1], "one");
    EXPECT_EQ(ht[2], "two");
}

TEST(HashTable, OperatorBracketCreatesDefault) {
    HashTable<int, std::string> ht;

    std::string& ref = ht[10];
    EXPECT_EQ(ref, ""); // default constructed string
}

TEST(HashTable, SizeAndEmpty) {
    HashTable<int, int> ht;

    EXPECT_TRUE(ht.empty());

    ht.insert(1, 10);
    ht.insert(2, 20);

    EXPECT_EQ(ht.size(), 2);
    EXPECT_FALSE(ht.empty());
}

TEST(HashTable, Clear) {
    HashTable<int, int> ht;

    ht.insert(1, 10);
    ht.insert(2, 20);

    ht.clear();

    EXPECT_TRUE(ht.empty());
    EXPECT_EQ(ht.size(), 0);
    EXPECT_FALSE(ht.find(1));
}

TEST(HashTable, AtFunction) {
    HashTable<int, std::string> ht;

    ht.insert(1, "one");

    EXPECT_EQ(ht.at(1), "one");

    EXPECT_THROW(ht.at(100), std::out_of_range);
}

TEST(HashTable, RehashPreservesData) {
    HashTable<int, int> ht;

    for (int i = 0; i < 100; i++) {
        ht.insert(i, i * 10);
    }

    for (int i = 0; i < 100; i++) {
        auto* v = ht.find(i);
        ASSERT_NE(v, nullptr);
        EXPECT_EQ(*v, i * 10);
    }

    EXPECT_EQ(ht.size(), 100);
}

int main(int ac, char **av) {
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
