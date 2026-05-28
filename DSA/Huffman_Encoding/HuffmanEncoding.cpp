#include "HuffmanEncoding.hpp"

size_t HuffmanEncoding::len = 0;
std::shared_ptr<Node> HuffmanEncoding::root = nullptr;
std::unordered_map<char, int> HuffmanEncoding::_counts;
std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>,Compare> HuffmanEncoding::pq;

void HuffmanEncoding::compute_counts(const std::string& text) {
	for (auto c : text) {
		if (_counts.find(c) == _counts.end())
			_counts[c] = 1;
		else
			++_counts[c];
	}
}

std::vector<uint8_t> HuffmanEncoding::encode(const std::string& text) {
	if (text.empty())
		return {};
	len = text.length();
	_counts.clear();
	pq = decltype(pq)();
	std::unordered_map<char, std::string> _codes;
	std::vector<uint8_t> encoded_text;

	compute_counts(text);
	root = building_tree();
	generate_codes(root, "", _codes);
	uint8_t current = 0;
	uint8_t bit_index = 0;
	for ( char ch : text) {
		const std::string& code = _codes[ch];
		for (char bit : code) {
			current <<= 1;
			if (bit == '1')
				current |= 1;
			bit_index++;
			if (bit_index == 8) {
				encoded_text.push_back(current);
				current = 0;
				bit_index = 0;
			}
		}
	}
	if (bit_index > 0) {
		current <<= (8 - bit_index);
		encoded_text.push_back(current);
	}
	return encoded_text;
}

std::shared_ptr<Node> HuffmanEncoding::building_tree() {
	for (const auto& it: _counts)
		pq.push(std::make_shared<Node>(it.first, it.second));
	while (pq.size() > 1) {
		auto left = pq.top();
		pq.pop();
		auto right = pq.top();
		pq.pop();
		pq.push(std::make_shared<Node>(left, right));
	}
	return pq.top();
}

bool HuffmanEncoding::is_leaf_node(const std::shared_ptr<Node>& node) {
	return node->left == nullptr && node->right == nullptr;
}

void HuffmanEncoding::generate_codes(const std::shared_ptr<Node>& node, std::string code, std::unordered_map<char, std::string>& _codes) {
	if (!node)
		return ;
	if (is_leaf_node(node)) {
		_codes[node->c] = code.empty() ? "0" : code;
		return ;
	}
	generate_codes(node->left, code + "0", _codes);
	generate_codes(node->right, code + "1", _codes);
}

std::string HuffmanEncoding::decode(const std::vector<uint8_t>& encoded_text) {
	if (encoded_text.size() == 0)
		return "";
	if (is_leaf_node(root))
		return std::string(len, root->c);
	std::string decoded_text;
	std::shared_ptr<Node> curr = root;
	for (auto raw : encoded_text) {
		for (int i = 7; i >= 0; --i) {
			if ((raw >> i) & 1)
				curr = curr->right;
			else
				curr = curr->left;
			if (is_leaf_node(curr)) {
				decoded_text += curr->c;
				if (decoded_text.length() == len)
					return decoded_text;
				curr = root;
			}
		}
	}
	return decoded_text;
}
