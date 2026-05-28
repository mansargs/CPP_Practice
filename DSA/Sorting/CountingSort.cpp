#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <iterator>

void counting_sort(std::vector<unsigned int>& vec) {
	std::vector<unsigned int> vec_copy(vec);
	size_t n = vec.size();
	unsigned max_val = *std::max_element(vec.cbegin(), vec.cend());
	std::vector<int> count(max_val + 1, 0);
	for (size_t i = 0; i < n; ++i)
		++count[vec[i]];
	for (size_t i = 1; i <= max_val; ++i)
		count[i] = count[i] + count[i - 1];
	for (size_t i = 0; i < n; ++i)
		vec[--count[vec_copy[i]]] = vec_copy[i];
}

int main() {
	static const int N = 10;
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution dist(0, 100);

	std::vector<unsigned int> vec(N);
	std::cout << "Unsorted vector\n";
	for (int i = 0; i < N; ++i) {
		vec[i] = dist(rng);
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	std::vector<unsigned int> v1(vec), v2(vec);
	counting_sort(v1);
	std::cout << "\nSorted vector\n";
	copy(v1.begin(), v1.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
	std::cout << std::endl;
	std::sort(v2.begin(), v2.end());
	if (v1 == v2)
		std::cout << "OK\n";
	else
		std::cout << "KO\n";
	return 0;
}
