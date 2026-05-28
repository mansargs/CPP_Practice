#include <iostream>
#include "Proxy.hpp"

int global_value = 10;

int return_value() {
	return 42;
}

int& return_lvalue() {
	return global_value;
}

int&& return_rvalue() {
	return std::move(global_value);
}

int main() {
	Proxy<decltype(return_value)> p1(return_value);
	std::cout << "value: " << p1.get() << "\n";

	Proxy<decltype(return_lvalue)> p2(return_lvalue);
	int& ref = p2.get();
	ref = 100;
	std::cout << "lvalue ref: " << global_value << "\n";

	Proxy<decltype(return_rvalue)> p3(return_rvalue);
	int&& r = p3.get();
	std::cout << "rvalue: " << r << "\n";
	return 0;
}
