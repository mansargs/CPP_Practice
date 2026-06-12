#pragma once

#include "Typeinfo.hpp"

struct VTable;
extern const VTable Base_vtable;

class Base {
	public:
		static inline const Typeinfo type_info{"Base", nullptr};
	
	protected:
		const VTable* vptr;
		bool derived_dtor_done_ = false;
	
		void mark_derived_dtor_done() { derived_dtor_done_ = true; }
	
	public:
		Base();
		/*virtual*/ ~Base();
	
		const VTable* get_vtable() const { return vptr; }
	
		/*virtual*/ void foo1();
		/*virtual*/ void foo2();
	
		void destroy();
	
		void dtor_body();
		void reset_vptr_to_base();
};
