#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <memory>

struct Node {
	std::shared_ptr<Node> left, right;
	char c;
	int freq;

	Node(char character, int frequency) : left(nullptr), right(nullptr), c(character), freq(frequency) {}
	Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r) : left(l), right(r), c('\0'), freq(l->freq + r->freq) {}
};

struct Compare {
	bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
		return a->freq > b->freq;
	}
};

class HuffmanEncoding {
	private:
		static size_t len;
		static std::shared_ptr<Node> root;
		static std::unordered_map<char, int> _counts;
		static std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Compare> pq;

		HuffmanEncoding() = delete;
		HuffmanEncoding(const HuffmanEncoding&) = delete;
		HuffmanEncoding& operator=(const HuffmanEncoding&) = delete;

		static std::shared_ptr<Node> building_tree();
		static void compute_counts(const std::string& text);
		static bool is_leaf_node(const std::shared_ptr<Node>& node);
		static void generate_codes(const std::shared_ptr<Node>& node, std::string code, std::unordered_map<char, std::string>& _codes);
	public:
		static std::vector<uint8_t> encode(const std::string& text);
		static std::string decode(const std::vector<uint8_t>& encoded);

};
