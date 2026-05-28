#include <iostream>

int main() {

	auto make_adder = [](auto value) {
		return [value](auto&& x) -> decltype(auto) {
			return std::forward<decltype(x)>(x) + value;
		};
	};


	auto transform_pair = [](auto&& a, auto&& b, auto&& op) -> decltype(auto) {
		return std::forward<decltype(op)>(op)(
			std::forward<decltype(a)>(a),
			std::forward<decltype(b)>(b)
		);
	};

	std::cout << "==== Test make_adder =====\n";
	double a = 9;
	auto add5 = make_adder(a);
	std::cout << add5(17) << std::endl;

	std::cout << "==== Test make_adder =====\n";
	std::cout << transform_pair(a, 15, [](auto&& a, auto&& b) {
		return std::forward<decltype(a)>(a) + std::forward<decltype(b)>(b);
	}) << std::endl;

	return 0;
}
