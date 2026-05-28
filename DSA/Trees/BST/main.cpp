#include <iostream>
#include "BST.hpp"

int main() {
	BST<int> tree;

	// Insert elements
	std::cout << "Inserting elements: 50, 30, 70, 20, 40, 60, 80\n";
	int values[] = {50, 30, 70, 20, 40, 60, 80};
	for (int v : values) {
		tree.insert(v);
	}

	// Traversals
	std::cout << "Inorder traversal: ";
	tree.inorder();  // should be sorted

	std::cout << "Preorder traversal: ";
	tree.preorder();

	std::cout << "Postorder traversal: ";
	tree.postorder();

	// Search test
	int search_vals[] = {40, 90};
	for (int v : search_vals) {
		auto node = tree.search(v);
		if (node)
			std::cout << "Found " << v << "\n";
		else
			std::cout << v << " not found\n";
	}

	// Height test
	std::cout << "Tree height: " << tree.height() << "\n";

	// Successor & Predecessor test
	int test_val = 50;
	auto succ = tree.get_successor(test_val);
	auto pred = tree.get_predecessor(test_val);
	if (succ) std::cout << "Successor of " << test_val << " is " << succ->value << "\n";
	else std::cout << "No successor for " << test_val << "\n";

	if (pred) std::cout << "Predecessor of " << test_val << " is " << pred->value << "\n";
	else std::cout << "No predecessor for " << test_val << "\n";

	// Delete test
	std::cout << "Deleting 20 (leaf), 30 (one child), 50 (two children)\n";
	tree.delete_node(tree.search(20));
	tree.delete_node(tree.search(30));
	tree.delete_node(tree.search(50));

	std::cout << "Inorder after deletions: ";
	tree.inorder();

	std::cout << "Final tree height: " << tree.height() << "\n";

	return 0;
}
