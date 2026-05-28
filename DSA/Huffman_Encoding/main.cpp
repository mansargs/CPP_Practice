#include "HuffmanEncoding.hpp"
#include <iostream>
#include <vector>

bool run_test(const std::string& text) {
	std::vector<uint8_t> encoded = HuffmanEncoding::encode(text);
	std::string decoded = HuffmanEncoding::decode(encoded);
	bool ok = (decoded == text);
	if (ok)
		std::cout << "✅ PASS\n";
	else
		std::cout << "❌ FAIL\n";
	return ok;
}

int main() {
	std::vector<std::string> tests;
	tests.push_back("a");
	tests.push_back("aa");
	tests.push_back("aaa");
	tests.push_back("aaaaaaa");
	tests.push_back("hello");
	tests.push_back("world");
	tests.push_back("huffman");
	tests.push_back("this is an example of huffman encoding");
	tests.push_back("abababababababab");
	tests.push_back("abcabcabcabc");
	tests.push_back("abcdefg");
	tests.push_back("aabbbccccddddeeeee");
	tests.push_back("Hello, World!");
	tests.push_back("C++ Huffman Encoding Test!");
	tests.push_back("");
	tests.push_back(std::string(10000, 'a'));
	tests.push_back(std::string(5000, 'a') + std::string(5000, 'b'));
	tests.push_back("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");

	for (size_t i = 0; i < tests.size(); ++i) {
		if (!run_test(tests[i])) {
			std::cout << "\n❌ TEST FAILED at index " << i << std::endl;
			return 1;
		}
	}
	std::cout << "\n🎉 ALL TESTS PASSED — YOUR HUFFMAN IS CORRECT!\n";
	return 0;
}
