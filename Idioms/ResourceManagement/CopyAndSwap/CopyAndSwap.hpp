#pragma once

#include <iostream>

class CopyAndSwap {
	private:
		int* p;
	public:

		friend void swap(CopyAndSwap& first, CopyAndSwap& second) noexcept {
			using std::swap;
			swap(first.p, second.p);
		}

		CopyAndSwap() {
			p = new int();
			std::cout << "Default ctor\n";
		}

		CopyAndSwap(const CopyAndSwap& oth) : p(new int(*oth.p)) {
			std::cout << "Copy ctor\n";
		}

		CopyAndSwap& operator=(CopyAndSwap oth) {
			swap(*this, oth);
			return *this;
		}

		~CopyAndSwap() {
			delete p;
			std::cout << "Dtor\n";
		}
};
