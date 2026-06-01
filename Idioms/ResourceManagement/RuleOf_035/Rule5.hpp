#pragma once

#include <iostream>

class Rule5 {
	private:
		int* p;
	public:
		Rule5() {
			p = new int();
			std::cout << "Default ctor\n";
		}

		Rule5(const Rule5& oth) {
			p = new int(*oth.p);
			std::cout << "Copy ctor\n";
		}

		Rule5& operator=(const Rule5& oth) {
			if (this != &oth) {
				delete p;
				p = new int(*oth.p);
			}
			std::cout << "Copy assignement\n";
			return *this;
		}

		Rule5(Rule5&& oth) noexcept : p(oth.p) {
			oth.p = nullptr;
			std::cout << "Move ctor\n";
		}

		Rule5& operator=(Rule5&& oth) noexcept {
			if (this != &oth) {
				delete p;
				p = oth.p;
				oth.p = nullptr;
			}
			std::cout << "Move assignment\n";
			return *this;
		}

		~Rule5() { delete p; }
};
