#include <iostream>
#include "Monadic.hpp"

std::unordered_map<int, std::string> table = {
	{1, "one"},
	{2, "two"},
	{3, "three"}
};

std::optional<int> parse_int(const std::string& s) {
	try {
		return std::stoi(s);
	} catch(...) {
		return std::nullopt;
	}
}

std::optional<int> validate_range(int x) {
	if (x < 1 || x > 3)
		return std::nullopt;
	return x;
}

std::optional<std::string> lookup(int x) {
	auto it = table.find(x);
	if (it == table.end())
		return std::nullopt;
	return it->second;
}

std::string format(const std::string& s) {
	return "Result: " + s;
}

