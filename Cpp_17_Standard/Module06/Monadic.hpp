#pragma once

#include <optional>
#include <string>
#include <unordered_map>

extern std::unordered_map<int, std::string> table;

template<typename T, typename F>
auto optional_map(const std::optional<T>& opt, F fn) {
	using U = std::decay_t<decltype(fn(*opt))>;
	if (!opt)
		return std::optional<U>{};
	return std::optional<U>{fn(*opt)};
}

template<typename T, typename F>
auto optional_and_then(const std::optional<T>& opt, F fn) {
	using R = decltype(fn(*opt));
	if (!opt)
		return R{};
	return fn(*opt);
}

std::optional<int> parse_int(const std::string& s);
std::optional<int> validate_range(int x);
std::optional<std::string> lookup(int x);
std::string format(const std::string& s);


