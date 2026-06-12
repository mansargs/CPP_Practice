#pragma once

#include "Base.hpp"
#include "VTable.hpp"

template <typename Target, typename Source>
[[nodiscard]] Target* my_dynamic_cast(Source* obj) {
	if (!obj)
		return nullptr;
	const Typeinfo* actual_type = obj->get_vtable()->info;
	const Typeinfo* target_type = &Target::type_info;
	if (!is_same_or_derived_from(target_type, actual_type))
		return nullptr;
	return static_cast<Target*>(obj);
}
