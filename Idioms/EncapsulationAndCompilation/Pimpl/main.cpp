#include "Logger.hpp"
#include <iostream>

int main() {
	std::cout << "=== Basic ===\n";
	Logger log;
	log.set_level(1);
	log.log("Hello world");
	std::cout << "\n=== Copy ===\n";
	Logger log2 = log;
	log2.log("Copy works");
	std::cout << "\n=== Move ===\n";
	Logger log3 = std::move(log);
	log3.log("Move works");
	std::cout << "\n=== Original after move ===\n";
	log3.set_level(0);
	log3.log("Should skip");
	return 0;
}
