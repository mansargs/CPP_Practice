#pragma once

#include <type_traits>

template<typename T>
constexpr std::remove_reference_t<T>&& my_move(T&& t) {
	return static_cast<std::remove_reference_t<T>&&>(t);
}
