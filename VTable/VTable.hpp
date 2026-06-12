#pragma once

#include "Typeinfo.hpp"

class Base;

struct VTable {
	const Typeinfo* info;
	void (*foo1)(Base*);
	void (*foo2)(Base*);
	void (*dtor)(Base*);     // D1: complete-object destructor
	void (*destroy)(Base*);  // D0: deleting destructor (D1 + operator delete)
};

extern const VTable Base_vtable;
extern const VTable Derived_vtable;
