#pragma once

#include <iostream>

class RAII {
	private:
		int* p;
	public:
		RAII() {
			p = new int();
			std::cout << "Ctor called\n";
		}

		~RAII() {
			delete p;
			std::cout << "Dtor called\n";
		}
};
