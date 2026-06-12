#pragma once

class Typeinfo {
	public:
		const char* name;
		const Typeinfo* base;
	
		constexpr Typeinfo(const char* class_name, const Typeinfo* base_info)
			: name(class_name), base(base_info) {}
};

inline bool is_same_or_derived_from(const Typeinfo* target_type, const Typeinfo* actual_type) {
	if (!target_type || !actual_type)
		return false;
	for (const Typeinfo* current = actual_type; current; current = current->base) {
		if (current == target_type)
			return true;
	}
	return false;
}
