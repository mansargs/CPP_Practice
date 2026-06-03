#pragma once

#include <utility>

template<typename First, typename Second>
struct Pair {
	First first;
	Second second;

	Pair(First f, Second s) : first(std::move(f)), second(std::move(s)) {}
};

template<typename First, typename Second>
Pair(First, Second) -> Pair<First, Second>;


