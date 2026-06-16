#pragma once

#include <type_traits>

template <class T>
constexpr T&& my_forward(std::remove_reference_t<T>& t) noexcept {
	return static_cast<T&&>(t);
}

template <class T>
constexpr T&& forward(std::remove_reference_t<T>&& t) noexcept {
	static_assert(std::is_lvalue_reference_v<T>, "std::forward must not forward an rvalue as an lvalue");
	return static_cast<T&&>(t);
}
