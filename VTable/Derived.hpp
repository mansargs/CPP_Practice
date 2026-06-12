#pragma once

#include "Base.hpp"

class Derived : public Base {
public:
	static inline const Typeinfo type_info{"Derived", &Base::type_info};

	Derived();
	/*virtual*/ ~Derived();

	/*virtual*/ void foo1();
	/*virtual*/ void foo2();

	void dtor_body();
};
