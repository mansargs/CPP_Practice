#pragma once

#include <memory>
#include <algorithm>
#include <iostream>

template <typename T>
struct Node {
	T value;
	std::shared_ptr<Node<T>> left, right;
	std::weak_ptr<Node<T>> parent;

	Node(const T& val) : value(val) {}
};

template <typename T>
class BST {
private:
	std::shared_ptr<Node<T>> root;
public:
	BST() : root(nullptr) {}

	void insert(const T& value) {
		auto node = std::make_shared<Node<T>>(value);
		std::shared_ptr<Node<T>>* curr = &root;
		std::shared_ptr<Node<T>> parent = nullptr;
		while (*curr) {
			parent = *curr;
			if (value < (*curr)->value)
				curr = &((*curr)->left);
			else if (value > (*curr)->value)
				curr = &((*curr)->right);
			else
				return;
		}
		node->parent = parent;
		*curr = node;
	}

	std::shared_ptr<Node<T>> search(const T& value) const {
		auto curr = root;
		while (curr) {
			if (value < curr->value)
				curr = curr->left;
			else if (value > curr->value)
				curr = curr->right;
			else
				return curr;
		}
		return nullptr;
	}

	int height(const std::shared_ptr<Node<T>>& node) const {
		if (!node)
			return -1;
		int l = height(node->left);
		int r = height(node->right);
		return std::max(l, r) + 1;
	}

	int height() const {
		return height(root);
	}

	std::shared_ptr<Node<T>> get_successor(const T& value) {
		auto node = search(value);
		if (!node)
			return nullptr;
		if (node->right) {
			node = node->right;
			while (node->left)
				node = node->left;
			return node;
		}
		auto parent = node->parent.lock();
		while (parent && parent->right == node) {
			node = parent;
			parent = parent->parent.lock();
		}
		return parent;
	}

	std::shared_ptr<Node<T>> get_predecessor(const T& value) {
		auto node = search(value);
		if (!node)
			return nullptr;
		if (node->left) {
			node = node->left;
			while (node->right)
				node = node->right;
			return node;
		}
		auto parent = node->parent.lock();
		while (parent && parent->left == node) {
			node = parent;
			parent =parent->parent.lock();
		}
		return parent;
	}


	void delete_node(std::shared_ptr<Node<T>> node) {
		if (!node)
			return;
		auto parent = node->parent.lock();


		if (!node->left && !node->right) {
			if (!parent) {
				root = nullptr;
			} else if (parent->left == node) {
				parent->left = nullptr;
			} else {
				parent->right = nullptr;
			}
			return;
		}
		if (!node->left || !node->right) {
			auto child = node->left ? node->left : node->right;
			if (!parent) {
				root = child;
				child->parent.reset();
			} else if (parent->left == node) {
				parent->left = child;
				child->parent = parent;
			} else {
				parent->right = child;
				child->parent = parent;
			}
			return;
		}
		auto successor = node->right;
		while (successor->left)
			successor = successor->left;
		node->value = successor->value;
		delete_node(successor);
	}

	void inorder(const std::shared_ptr<Node<T>>& node) const {
		if (!node)
			return;
		inorder(node->left);
		std::cout << node->value << " ";
		inorder(node->right);
	}

	void inorder() const {
		inorder(root);
		std::cout << "\n";
	}

	void preorder(const std::shared_ptr<Node<T>>& node) const {
		if (!node)
			return;
		std::cout << node->value << " ";
		preorder(node->left);
		preorder(node->right);
	}

	void preorder() const {
		preorder(root);
		std::cout << "\n";
	}

	void postorder(const std::shared_ptr<Node<T>>& node) const {
		if (!node)
			return;
		postorder(node->left);
		postorder(node->right);
		std::cout << node->value << " ";
	}

	void postorder() const {
		postorder(root);
		std::cout << "\n";
	}

	std::shared_ptr<Node<T>> get_root() const {
		return root;
	}
};
