#include <iostream>
#include <tuple>
#include <string>
#include "Apply.hpp"

void print(int a, const std::string& s, double d) {
	std::cout << a << ' ' << s << ' ' << d << std::endl;
}

int main() {
	auto t = std::make_tuple(235, std::string("string"), 325.32);
	::apply(print, t);
}
