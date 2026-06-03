#pragma once

#include <type_traits>
#include <iostream>
#include <tuple>

template<typename... Ts>
auto sum(const Ts&... args) {
	return (args + ...);
}

template<typename... Ts>
auto product(const Ts&... args) {
	return (args * ...);
}

template<typename First, typename... Rest>
bool all_same_type(const First&, const Rest&...) {
	return (std::is_same_v<First, Rest> && ...);
}

template<typename... Ts>
void print_all(const Ts&... args) {
	((std::cout << args << ' '), ...);
}

template<typename T>
T clamp(T x, T lo, T hi) {
	if (x < lo) return lo;
	if (x > hi) return hi;
	return x;
}

template<typename... Ts, typename T>
auto clamp_all(T lo, T hi, Ts... xs) {
	return std::make_tuple(clamp(xs, lo, hi)...);
}
