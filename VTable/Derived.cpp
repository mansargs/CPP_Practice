#include "Derived.hpp"

#include "VTable.hpp"

#include <iostream>

Derived::Derived() : Base() {
	vptr = &Derived_vtable;
	std::cout << "Derived ctor called\n";
}

void Derived::dtor_body() {
	std::cout << "Derived dtor called\n";
}

Derived::~Derived() {
	dtor_body();
	mark_derived_dtor_done();
}

void Derived::foo1() {
	std::cout << "Derived::foo1 called\n";
}

void Derived::foo2() {
	std::cout << "Derived::foo2 called\n";
}
