#include <iostream>
#include "LRUCache.hpp"

int main() {
	LRUCache<int, std::string> cache(2);
	cache.put(1, "one");
	cache.put(2, "two");
	auto v1 = cache.get(1);
	if (v1)
		std::cout << "get(1): " << *v1 << std::endl;
	else
		std::cout << "get(1): not found\n";
	cache.put(3, "three");
	auto v2 = cache.get(2);
	if (v2)
		std::cout << "get(2): " << *v2 << std::endl;
	else
		std::cout << "get(2): not found\n";
	auto v3 = cache.get(3);
	if (v3) std::cout << "get(3): " << *v3 << std::endl;
	return 0;
}
