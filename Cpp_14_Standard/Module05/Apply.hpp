#pragma once

#include <utility>

template<typename F, typename Tuple, std::size_t... I>
auto call_impl(F&& fn, Tuple&& t, std::index_sequence<I...>) {
	return fn(std::get<I>(t)...);
}

template<typename F, typename Tuple>
void apply(F&& fn, Tuple&& t) {
	constexpr auto size = std::tuple_size<std::decay_t<Tuple>>::value;
	return call_impl(std::forward<F>(fn), std::forward<Tuple>(t), std::make_index_sequence<size>{});
}
