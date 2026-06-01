#pragma once

#include <string>
#include <iostream>

class Rule0 {
	private:
		std::string s;
	public:
		Rule0(const std::string& text) : s(text) {
			std::cout << "Default ctor\n";
		}

		const std::string& get() const {
			return s;
		}

		void set(const std::string& text) { s = text; }
};
