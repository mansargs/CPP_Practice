#pragma once

#include <iostream>

class Rule3 {
	private:
		int* p;
	public:
		Rule3() {
			p = new int();
			std::cout << "Default ctor\n";
		}

		Rule3(const Rule3& oth) {
			p = new int(*oth.p);
			std::cout << "Copy ctor\n";
		}

		Rule3& operator=(const Rule3& oth) {
			if (this != &oth) {
				delete p;
				p = new int(*oth.p);
			}
			std::cout << "Copy assignement\n";
			return *this;
		}

		~Rule3() { delete p; }
};
