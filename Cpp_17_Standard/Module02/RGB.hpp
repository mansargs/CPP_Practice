#pragma once

#include <cstdlib>
#include <type_traits>
#include <tuple>

struct RGB {
	int r, g, b;
};

namespace std {
	template<>
	struct tuple_size<RGB> : std::integral_constant<size_t, 3> {};

	 template<>
	struct tuple_element<0, RGB> { using type = int; };

	template<>
	struct tuple_element<1, RGB> { using type = int; };

	template<>
	struct tuple_element<2, RGB> { using type = int; };
}

template<std::size_t N>
auto& get(RGB& c) {
	if constexpr(N == 0) return c.r;
	else if constexpr(N == 1) return c.g;
	else if constexpr(N == 2) return c.b;
}

template<std::size_t N>
const auto& get(const RGB& c) {
	if constexpr(N == 0) return c.r;
	else if constexpr(N == 1) return c.g;
	else if constexpr(N == 2) return c.b;
}

template<std::size_t N>
auto&& get(RGB&& c) {
	if constexpr (N == 0) return std::move(c.r);
	else if constexpr (N == 1) return std::move(c.g);
	else return std::move(c.b);
}

template<std::size_t N>
const auto&& get(const RGB&& c) {
	if constexpr (N == 0) return std::move(c.r);
	else if constexpr (N == 1) return std::move(c.g);
	else return std::move(c.b);
}
