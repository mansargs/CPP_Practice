#include <iostream>
#include <vector>
#include "RedBlackTree.hpp"
using namespace std;

template<typename T>
void inorder_color(const Node<T>* node) {
	if (!node)
		return;
	inorder_color(node->left);
	cout << node->value << "("
		 << (node->color == RED ? "R" : "B") << ") ";
	inorder_color(node->right);
}

template <typename T>
bool check_no_red_red(const Node<T>* node) {
	if (!node)
		return true;
	if (node->color == RED) {
		if ((node->left && node->left->color == RED) ||
			(node->right && node->right->color == RED))
			return false;
	}

	return check_no_red_red(node->left) &&
			check_no_red_red(node->right);
}

int black_height(const Node<int>* node) {
	if (!node)
		return 1;
	int left = black_height(node->left);
	int right = black_height(node->right);
	if (left == 0 || right == 0 || left != right)
		return 0;
	return left + (node->color == BLACK ? 1 : 0);
}

void print_state(RedBlackTree<int>& tree, const string& msg) {
	cout << "\n=== " << msg << " ===\n";
	cout << "Inorder (value+color): ";
	inorder_color(tree.get_root());
	cout << "\nRoot: ";
	if (tree.get_root())
		cout << tree.get_root()->value
			 << (tree.get_root()->color == RED ? "(R)" : "(B)") << "\n";
	else
		cout << "NULL\n";
}

void validate_tree(RedBlackTree<int>& tree) {
	cout << "\n=== VALIDATION ===\n";
	bool no_red_red = check_no_red_red(tree.get_root());
	int bh = black_height(tree.get_root());
	cout << "No red-red violation: "
		 << (no_red_red ? "OK" : "FAIL") << "\n";
	cout << "Black-height valid: "
		 << (bh != 0 ? "OK" : "FAIL") << "\n";
}

int main() {

	RedBlackTree<int> tree;

	cout << "============================\n"
		 << " RED-BLACK TREE FULL TESTER\n"
		 << "============================\n";

	vector<int> insertValues = {
		50, 30, 70, 20, 40, 60, 80,
		10, 25, 35, 45, 55, 65, 75, 90,
		5, 15, 22, 27, 33, 37, 42, 47
	};

	cout << "\n[INSERT PHASE]\n";
	for (int v : insertValues)
		tree.insert(v);

	print_state(tree, "After Insertions");
	validate_tree(tree);

	cout << "\n[SEARCH PHASE]\n";
	cout << "Search 25: " << (tree.search(25) ? "FOUND" : "NOT FOUND") << "\n";
	cout << "Search 100: " << (tree.search(100) ? "FOUND" : "NOT FOUND") << "\n";

	vector<int> deleteValues = {
		5, 10, 25, 50, 70, 80, 90, 100
	};

	cout << "\n[DELETE PHASE]\n";
	for (int v : deleteValues) {
		cout << "Deleting: " << v << endl;
		tree.remove(v);
	}

	print_state(tree, "After Deletions");
	validate_tree(tree);

	vector<int> wipeValues = {
		20, 30, 40, 60, 65, 75, 35, 37, 42, 45, 47
	};

	cout << "\n[FULL WIPE]\n";
	for (int v : wipeValues) {
		cout << "Deleting: " << v << endl;
		tree.remove(v);
	}

	print_state(tree, "Final State");
	validate_tree(tree);

	cout << "\n============================\n";
	cout << " TEST COMPLETED\n";
	cout << "============================\n";

	return 0;
}
