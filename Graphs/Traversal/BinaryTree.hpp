#ifndef BINARYTREE_HPP
# define BINARYTREE_HPP

#include <memory>

class Node {
	public:
		int value;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;

		explicit Node(int val) : value(val) , left(nullptr), right(nullptr) {}
};

class BinaryTree {
	private:
		std::shared_ptr<Node> recursiveInsert(std::shared_ptr<Node> node, int value) {
			if (!node)
				return std::make_shared<Node>(value);
			if (value < node->value)
				node->left = recursiveInsert(node->left, value);
			else
				node->right = recursiveInsert(node->right, value);
			return node;
		}
	public:
		std::shared_ptr<Node> root;

		BinaryTree() : root(nullptr) {}

		void insert(int val) {
			root = recursiveInsert(root, val);
		}

		std::shared_ptr<Node> getRoot() const {
			return root;
		}
};

#endif
