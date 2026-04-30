#pragma once

#include <iostream>
#include <algorithm>

template<typename T>
struct Node {
	T value;
	int height;
	Node* left;
	Node* right;

	Node(const T& value)
		: value(value), height(0), left(nullptr), right(nullptr) {}
};

template<typename T>
class AVL {
	private:
		Node<T>* root = nullptr;

		int height(Node<T>* node) {
			return node ? node->height : -1;
		}

		int count_nodes(Node<T>* node) const{
			if (!node)
				return 0;
			return 1 + count_nodes(node->left) + count_nodes(node->right);
		}

		int get_balance(Node<T>* node) {
			return node ? height(node->left) - height(node->right) : 0;
		}

		void update_height(Node<T>* node) {
			node->height = 1 + std::max(height(node->left), height(node->right));
		}

		Node<T>* ll_rotation(Node<T>* y) {
			Node<T>* x = y->left;
			Node<T>* t2 = x->right;
			x->right = y;
			y->left = t2;
			update_height(y);
			update_height(x);
			return x;
		}

		Node<T>* rr_rotation(Node<T>* y) {
			Node<T>* x = y->right;
			Node<T>* t2 = x->left;
			x->left = y;
			y->right = t2;
			update_height(y);
			update_height(x);
			return x;
		}

		Node<T>* rebalance(Node<T>* node) {
			if (!node)
				return node;
			update_height(node);
			int bf = get_balance(node);
			if (bf > 1 && get_balance(node->left) >= 0)
				return ll_rotation(node);
			if (bf > 1 && get_balance(node->left) < 0) {
				node->left = rr_rotation(node->left);
				return ll_rotation(node);
			}
			if (bf < -1 && get_balance(node->right) <= 0)
				return rr_rotation(node);
			if (bf < -1 && get_balance(node->right) > 0) {
				node->right = ll_rotation(node->right);
				return rr_rotation(node);
			}
			return node;
		}

		Node<T>* insert(Node<T>* node, T value) {
			if (!node)
				return new Node<T>(value);
			if (value < node->value)
				node->left = insert(node->left, value);
			else if (value > node->value)
				node->right = insert(node->right, value);
			else
				return node;
			return rebalance(node);
		}

		Node<T>* get_min(Node<T>* node) {
			while (node && node->left)
				node = node->left;
			return node;
		}

		Node<T>* delete_node(Node<T>* node, T value) {
			if (!node)
				return nullptr;
			if (value < node->value)
				node->left = delete_node(node->left, value);
			else if (value > node->value)
				node->right = delete_node(node->right, value);
			else {
				if (!node->left || !node->right) {
					Node<T>* temp = node->left ? node->left : node->right;
					if (!temp) {
						delete node;
						return nullptr;
					} else {
						*node = *temp;
						delete temp;
					}
				}
				else {
					Node<T>* succ = get_min(node->right);
					node->value = succ->value;
					node->right = delete_node(node->right, succ->value);
				}
			}

			return rebalance(node);
		}

		void destroy(Node<T>* node) {
			if (!node) return;
			destroy(node->left);
			destroy(node->right);
			delete node;
		}

		void inorder(Node<T>* node) const {
			if (!node)
				return;
			inorder(node->left);
			std::cout << node->value << " ";
			inorder(node->right);
		}

		void preorder(Node<T>* node) const {
			if (!node)
				return;
			std::cout << node->value << " ";
			preorder(node->left);
			preorder(node->right);
		}

		void postorder(Node<T>* node) const {
			if (!node)
				return;
			postorder(node->left);
			postorder(node->right);
			std::cout << node->value << " ";
		}

	public:
		void insert(T value) {
			root = insert(root, value);
		}

		void remove(T value) {
			root = delete_node(root, value);
		}

		Node<T>* get_root() {
			return root;
		}

		void print_inorder() const {
			inorder(root);
			std::cout << "\n";
		}

		void print_preorder() const {
			preorder(root);
			std::cout << "\n";
		}

		void print_postorder() const {
			postorder(root);
			std::cout << "\n";
		}

		size_t size() const {
			return count_nodes(root);
		}

		size_t height() const {
			if (!root)
				return 0;
			return root->height;
		}

		~AVL() {
			destroy(root);
		}
	};
