#pragma once

#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>

struct Node {
	std::unordered_map<char, Node*> children;
	std::vector<std::string> topK;
	bool isWord;

	Node() : isWord(false) {}
};

class Trie {
	private:
		Node* root;
		unsigned K;
		std::unordered_map<std::string, unsigned> freq;

		void updateTopK(Node* curr, const std::string& word) {
			auto& v = curr->topK;
			v.erase(std::remove(v.begin(), v.end(), word), v.end());
			v.push_back(word);
			std::sort(v.begin(), v.end(), [&](const std::string& a, const std::string& b) {
				if(freq[a] == freq[b])
					return a < b;
				return freq[a] > freq[b];
			});
			if (v.size() > K)
				v.resize(K);
		}

	public:
		Trie(unsigned k = 4) {
			root = new Node();
			K = k;
		}

		void insert(const std::string& word) {
			Node* curr = root;
			freq[word]++;
			for(char c : word) {
				if (!curr->children.count(c))
					curr->children[c] = new Node();
				curr = curr->children[c];
				updateTopK(curr, word);
			}
			curr->isWord = true;
		}

		bool search(const std::string& word) {
			Node* curr = root;
			for (char c : word) {
				if (!curr->children.count(c))
					return false;
				curr = curr->children[c];
			}
			return curr->isWord;
		}

		bool startsWith(const std::string& prefix) {
			Node* curr = root;
			for (char c : prefix) {
				if (!curr->children.count(c))
					return false;
				curr = curr->children[c];
			}
			return true;
		}

		void increaseFrequency(const std::string& word) {
			freq[word]++;
			Node* curr = root;
			for(char c : word) {
				if (!curr->children.count(c))
					return ;
				curr = curr->children[c];
				updateTopK(curr, word);
			}
		}

		std::vector<std::string> getSuggestions(std::string prefix) {
			Node* curr = root;
			for (char c : prefix) {
				if (!curr->children.count(c))
					return {};
				curr = curr->children[c];
			}
			return curr->topK;
		}
};
