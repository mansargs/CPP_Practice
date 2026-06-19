#include <gtest/gtest.h>
#include "Trie.hpp"

TEST(TrieBasic, SearchTests) {
	Trie trie;

	trie.insert("cat");
	trie.insert("car");
	trie.insert("cart");
	trie.insert("dog");

	EXPECT_TRUE(trie.search("cat"));
	EXPECT_TRUE(trie.search("car"));
	EXPECT_TRUE(trie.search("cart"));
	EXPECT_TRUE(trie.search("dog"));

	EXPECT_FALSE(trie.search("cab"));
	EXPECT_FALSE(trie.search("ca"));
	EXPECT_FALSE(trie.search("do"));
	EXPECT_FALSE(trie.search("z"));
}

TEST(TrieBasic, PrefixTests) {
	Trie trie;

	trie.insert("cat");
	trie.insert("car");
	trie.insert("cart");
	trie.insert("dog");

	EXPECT_TRUE(trie.startsWith("ca"));
	EXPECT_TRUE(trie.startsWith("car"));
	EXPECT_TRUE(trie.startsWith("do"));

	EXPECT_FALSE(trie.startsWith("xyz"));
	EXPECT_FALSE(trie.startsWith("z"));
}

TEST(TrieBasic, InsertTests) {
	Trie trie;

	EXPECT_FALSE(trie.search("cap"));

	trie.insert("cap");

	EXPECT_TRUE(trie.search("cap"));
	EXPECT_TRUE(trie.startsWith("ca"));
}

TEST(TrieAdvanced, FrequencyTests) {
	Trie trie;

	trie.insert("cat");
	trie.insert("car");
	trie.insert("cart");

	trie.increaseFrequency("car");
	trie.increaseFrequency("car");
	trie.increaseFrequency("cat");

	auto res = trie.getSuggestions("ca");

	ASSERT_FALSE(res.empty());
	EXPECT_EQ(res[0], "car");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
