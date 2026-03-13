#include <iostream>
#include <stack>
#include "BinaryTree.hpp"

void preOrderRec(std::shared_ptr<Node> node) {
	if (!node)
		return ;
	std::cout << node->value << " ";
	preOrderRec(node->left);
	preOrderRec(node->right);
}

void inOrderRec(std::shared_ptr<Node> node) {
	if (!node)
		return ;
	inOrderRec(node->left);
	std::cout << node->value << " ";
	inOrderRec(node->right);
}

void postOrderRec(std::shared_ptr<Node> node) {
	if (!node)
		return ;
	postOrderRec(node->left);
	postOrderRec(node->right);
	std::cout << node->value << " ";
}

void preOrder(std::shared_ptr<Node> root) {
	std::stack<std::shared_ptr<Node>> st;

	if (root)
		st.push(root);
	while (!st.empty()) {
		auto node = st.top();
		st.pop();
		std::cout << node->value << " ";
		if (node->right)
			st.push(node->right);
		if (node->left)
			st.push(node->left);
	}
}

void inOrder(std::shared_ptr<Node> root) {
	std::stack<std::shared_ptr<Node>> st;
	auto curr = root;

	while (curr || !st.empty()) {
		while (curr) {
			st.push(curr);
			curr = curr->left;
		}
		curr = st.top();
		st.pop();
		std::cout << curr->value << " ";
		curr =curr->right;
	}
}

void postOrder(std::shared_ptr<Node> root) {
	std::stack<std::shared_ptr<Node>> s1, s2;

	if (root)
		s1.push(root);
	while (!s1.empty()) {
		auto node = s1.top();
		s1.pop();
		s2.push(node);
		if (node->left)
			s1.push(node->left);
		if (node->right)
			s1.push(node->right);
	}
	while (!s2.empty()) {
		std::cout << s2.top()->value << " ";
		s2.pop();
	}
}

int dfs(std::shared_ptr<Node> node) {
	static int count = 0;
	if (!node)
		return count;
	count++;
	std::cout << node->value << " ";
	dfs(node->left);
	dfs(node->right);
	return count;
}

int main () {
	BinaryTree tree;

	tree.insert(10);
	tree.insert(324);
	tree.insert(2);
	tree.insert(35);
	tree.insert(100);
	tree.insert(32);
	tree.insert(2321);
	tree.insert(233);
	tree.insert(23);

	std::cout << " <------------    Pre Order ------->\n";
	preOrder(tree.getRoot());
	std::cout << std::endl;
	preOrderRec(tree.getRoot());
	std::cout << std::endl;

	std::cout << " <------------    In Order ------->\n";
	inOrder(tree.getRoot());
	std::cout << std::endl;
	inOrderRec(tree.getRoot());
	std::cout << std::endl;

	std::cout << " <------------    Post Order ------->\n";
	postOrder(tree.getRoot());
	std::cout << std::endl;
	postOrderRec(tree.getRoot());
	std::cout << std::endl;

	std::cout << " <------------    DFS ------->\n";
	int count = dfs(tree.getRoot());
	std::cout << "\nHas " << count << " node(s)\n";
}
