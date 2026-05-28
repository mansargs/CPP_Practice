#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "AVL.hpp"

int main() {
	srand(time(nullptr));

	AVL<int> tree;
	std::cout << "=== BASIC INSERT ===\n";
	std::vector<int> values = {10, 5, 15, 3, 7, 12, 18};
	for (int x : values)
		tree.insert(x);
	std::cout << "Size: " << tree.size() << "\n";
	std::cout << "Height: " << tree.height() << "\n";
	std::cout << "Inorder: ";
	tree.print_inorder();

	std::cout << "\n=========================\n";
	std::cout << "=== DELETE TEST ===\n";
	tree.remove(3);
	tree.remove(5);
	tree.remove(10);

	std::cout << "After deletions:\n";
	std::cout << "Size: " << tree.size() << "\n";
	std::cout << "Height: " << tree.height() << "\n";
	std::cout << "Inorder: ";
	tree.print_inorder();

	std::cout << "\n=========================\n";
	std::cout << "=== SORTED INSERT TEST ===\n";

	AVL<int> t1;
	for (int i = 0; i < 100; ++i)
		t1.insert(i);
	std::cout << "Size: " << t1.size() << "\n";
	std::cout << "Height: " << t1.height() << "\n";
	t1.print_inorder();

	std::cout << "\n=========================\n";
	std::cout << "=== REVERSE INSERT TEST ===\n";

	AVL<int> t2;
	for (int i = 100; i >= 0; --i)
		t2.insert(i);
	std::cout << "Size: " << t2.size() << "\n";
	std::cout << "Height: " << t2.height() << "\n";
	t2.print_inorder();

	std::cout << "\n=========================\n";
	std::cout << "=== RANDOM STRESS TEST (10k ops) ===\n";

	AVL<int> stress;

	for (int i = 0; i < 10000; ++i) {
		int op = rand() % 2;
		int val = rand() % 5000;

		if (op == 0)
			stress.insert(val);
		else
			stress.remove(val);
	}

	std::cout << "Final inorder (partial): ";
	std::cout << "Size: " << stress.size() << "\n";
	std::cout << "Height: " << stress.height() << "\n";
	stress.print_inorder();

	std::cout << "\n=========================\n";
	std::cout << "=== HEAVY STRESS TEST (50k ops) ===\n";

	AVL<int> big;

	for (int i = 0; i < 50000; ++i) {
		int op = rand() % 2;
		int val = rand() % 100000;

		if (op == 0)
			big.insert(val);
		else
			big.remove(val);
	}

	std::cout << "Heavy stress done\n";
	std::cout << "Size: " << big.size() << "\n";
	std::cout << "Height: " << big.height() << "\n";
	std::cout << "Inorder (partial check): ";
	big.print_inorder();

	std::cout << "\n=== ALL TESTS COMPLETED ===\n";

	return 0;
}
