#include "Buffer.hpp"

int main() {
	std::cout << "=== Create buffer A ===\n";
	Buffer a(5);
	a.print();
	std::cout << "\n=== Move construct B from A ===\n";
	Buffer b(std::move(a));
	b.print();
	a.print();
	std::cout << "\n=== Create buffer C ===\n";
	Buffer c(10);
	c.print();
	std::cout << "\n=== Move assign C = B ===\n";
	c = std::move(b);
	std::cout << "\nAfter move assignment:\n";
	c.print();
	b.print();
	std::cout << "\n=== End of program ===\n";
	return 0;
}
