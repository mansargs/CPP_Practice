#pragma once

#include <utility>
#include <type_traits>

template <typename F>
class Proxy {
	private:
		std::decay_t<F> callable;
	
	public:
		template <typename Fn>
		Proxy(Fn&& fn)
			: callable(std::forward<Fn>(fn)) {}
	
		decltype(auto) get() {
			return callable();
		}
};
