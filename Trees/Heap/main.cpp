#include <iostream>
#include "Heap.hpp"

int main() {
	Heap<int, std::greater<int>> h;

	std::cout << "=== INSERT TEST ===\n";
	h.insert(5);
	h.insert(3);
	h.insert(8);
	h.insert(1);
	h.insert(6);

	std::cout << "Top should be 8: " << h.top() << "\n";

	std::cout << "\n=== POP TEST ===\n";
	while (!h.empty()) {
		std::cout << h.top() << " ";
		h.pop();
	}
	std::cout << "\n";

	std::cout << "\n=== HEAPIFY TEST ===\n";
	Heap<int> h2;

	h2.insert(10);
	h2.insert(4);
	h2.insert(7);
	h2.insert(2);
	h2.insert(9);
	std::cout << "Top should be 2: " << h2.top() << "\n";
	std::cout << "\n=== REMOVE TEST ===\n";
	Heap<int> h3;
	h3.insert(10);
	h3.insert(4);
	h3.insert(7);
	h3.insert(2);
	h3.insert(9);
	std::cout << "Before remove, top: " << h3.top() << "\n";
	h3.remove(2);
	std::cout << "After removing 2, new top: " << h3.top() << "\n";
	h3.remove(7);
	std::cout << "After removing 7, top: " << h3.top() << "\n";
	std::cout << "\nRemaining elements:\n";
	while (!h3.empty()) {
		std::cout << h3.top() << " ";
		h3.pop();
	}
	std::cout << "\n";
	return 0;
}
