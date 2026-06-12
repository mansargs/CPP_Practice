#include <iostream>

#include "Base.hpp"
#include "Derived.hpp"
#include "Dynamic_cast.hpp"

int main() {
	// --- dispatch examples ---
	Base* base = new Base();
	base->foo1();
	base->destroy();

	std::cout << "---\n";

	Derived* derived = new Derived();
	derived->foo1();
	derived->destroy();

	std::cout << "---\n";

	Base* poly = new Derived();
	poly->foo1();
	poly->destroy();

	// --- cast examples ---
	std::cout << "--- casts ---\n";

	Base* b1 = new Base();
	if (my_dynamic_cast<Derived>(b1) == nullptr) {
		std::cout << "Base* -> Derived*: nullptr (correct, object is Base)\n";
	} else {
		std::cout << "Base* -> Derived*: success (unexpected)\n";
	}
	b1->destroy();

	Base* b2 = new Derived();
	if (Derived* d2 = my_dynamic_cast<Derived>(b2)) {
		std::cout << "Base* -> Derived*: success (object is really Derived)\n";
		d2->foo1();
	} else {
		std::cout << "Base* -> Derived*: failed\n";
	}
	b2->destroy();

	Derived* d3 = new Derived();
	if (Base* up = my_dynamic_cast<Base>(d3)) {
		std::cout << "Derived* -> Base*: success (upcast)\n";
		up->foo1();
	}
	d3->destroy();

	if (my_dynamic_cast<Derived>(static_cast<Base*>(nullptr)) == nullptr) {
		std::cout << "nullptr cast: nullptr (correct)\n";
	} else {
		std::cout << "nullptr cast: unexpected success\n";
	}

	return 0;
}
