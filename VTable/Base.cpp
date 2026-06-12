#include "Base.hpp"

#include "VTable.hpp"

#include <iostream>

Base::Base() : vptr(&Base_vtable) {
	std::cout << "Base ctor called\n";
}

void Base::reset_vptr_to_base() {
	vptr = &Base_vtable;
}

void Base::dtor_body() {
	reset_vptr_to_base();
	std::cout << "Base dtor called\n";
}

Base::~Base() {
	if (!derived_dtor_done_) {
		vptr->dtor(this);
		return;
	}
	dtor_body();
}

void Base::foo1() {
	vptr->foo1(this);
}

void Base::foo2() {
	vptr->foo2(this);
}

void Base::destroy() {
	vptr->destroy(this);
}
