#include <functional>
#include <iostream>

int main() {
	auto make_light = []() {
		return [state = 0]() mutable {
			state = (state + 1) % 3;
			switch (state) {
				case 0:
				std::cout << "Red\n";
					break;
				case 1:
					std::cout << "Yellow\n";
					break;
				case 2:
					std::cout << "Green\n";
			}
		};
	};
	std::function<void()> light1 = make_light();
	std::function<void()> light2 = make_light();
	std::cout << "Light 1:\n";
	light1();
	light1();
	light1();
	std::cout << "\nLight 2:\n";
	light2();
	light2();
	light2();
	return 0;
}
