#include "VTable.hpp"

#include "Base.hpp"
#include "Derived.hpp"

#include <iostream>
#include <new>

namespace {

void base_dtor(Base* obj) {
	obj->dtor_body();
}

void derived_dtor(Base* obj) {
	static_cast<Derived*>(obj)->dtor_body();
	static_cast<Base*>(obj)->dtor_body();
}

void base_destroy(Base* obj) {
	base_dtor(obj);
	::operator delete(obj);
}

void derived_destroy(Base* obj) {
	derived_dtor(obj);
	::operator delete(obj);
}

void derived_foo1(Base* obj) {
	static_cast<Derived*>(obj)->foo1();
}

void derived_foo2(Base* obj) {
	static_cast<Derived*>(obj)->foo2();
}

void base_foo1(Base* obj) {
	(void)obj;
	std::cout << "Base::foo1 called\n";
}

void base_foo2(Base* obj) {
	(void)obj;
	std::cout << "Base::foo2 called\n";
}

}  // namespace

const VTable Base_vtable{
	&Base::type_info,
	base_foo1,
	base_foo2,
	base_dtor,
	base_destroy,
};

const VTable Derived_vtable{
	&Derived::type_info,
	derived_foo1,
	derived_foo2,
	derived_dtor,
	derived_destroy,
};
