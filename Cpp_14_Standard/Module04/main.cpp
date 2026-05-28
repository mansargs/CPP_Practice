#include "traits.hpp"
#include <iostream>

int main() {
	std::cout << std::boolalpha;
	std::cout << "int is integral: " << is_integral<int>::value << "\n";
	std::cout << "double is integral: " << is_integral<double>::value << "\n";
	std::cout << "char is integral: " << is_integral<char>::value << "\n";
	std::cout << "float is floating: " << is_floating_point<float>::value << "\n";
	std::cout << "int is floating: " << is_floating_point<int>::value << "\n";
	std::cout << "int is arithmetic: " << is_arithmetic<int>::value << "\n";
	std::cout << "float is arithmetic: " << is_arithmetic<float>::value << "\n";
	std::cout << "string is arithmetic: " << is_arithmetic<std::string>::value << "\n";
	std::cout << "zero int: " << zero<int>::value << "\n";
	std::cout << "zero float: " << zero<float>::value << "\n";
	std::cout << "zero double: " << zero<double>::value << "\n";
	return 0;
}
