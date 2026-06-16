#include "move.hpp"

#include <iostream>

class A {
	public:
		A() {
			std::cout << "Defualt\n";
		}

		A(const A& oth) {
			(void)oth;
			std::cout << "Copy\n";
		}

		A(A&& oth) noexcept {
			(void)oth;
			std::cout << "Move\n";
		}
};

int main() {
	A obj1;
	A obj2 = obj1;
	A obj3 = my_move(obj2);
	(void)obj3;
	return 0;
}
