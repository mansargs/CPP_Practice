#include <iostream>
#include <vector>
#include "Rule0.hpp"
#include "Rule3.hpp"
#include "Rule5.hpp"

int main() {
	std::cout << "===== Rule of 0 =====\n";
	{
		Rule0 a("hello");
		Rule0 b = a;
		b.set("world");
		std::cout << "a: " << a.get() << "\n";
		std::cout << "b: " << b.get() << "\n";
	}
	std::cout << "\n===== Rule of 3 =====\n";
	{
		Rule3 a;
		Rule3 b = a;
		Rule3 c;
		c = a;
	}
	std::cout << "\n===== Rule of 5 =====\n";
	{
		Rule5 a;
		Rule5 b = a;
		Rule5 c = std::move(a);
		Rule5 d;
		d = std::move(b);
	}
	std::cout << "\n===== Vector Behavior (IMPORTANT) =====\n";
	{
		std::vector<Rule5> vec;
		vec.push_back(Rule5());
		vec.emplace_back();
		Rule5 x;
		vec.push_back(x);
		vec.push_back(std::move(x));
	}
	return 0;
}
