#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <array>
#include <iterator>

static void counting_sort(std::vector<unsigned>& vec, int exp) {
	size_t n = vec.size();
	std::array<unsigned, 10> count = {0};
	std::vector<unsigned> vec_copy(vec);

	for (size_t i = 0; i < n; ++i)
		++count[(vec_copy[i] / exp) % 10];
	for (size_t i = 1; i < 10; ++i)
		count[i] = count[i] + count[i - 1];
	for (int i = n - 1; i >= 0; --i)
		vec[--count[(vec_copy[i] / exp) % 10]] = vec_copy[i];
}

void radix_sort(std::vector<unsigned>& vec) {
	unsigned max_val = *std::max_element(vec.begin(), vec.end());
	for (int exp = 1; max_val / exp > 0; exp *= 10)
		counting_sort(vec, exp);
}

int main() {
	static const int N = 10;
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution dist(0, 10000);

	std::vector<unsigned int> vec(N);
	std::cout << "Unsorted vector\n";
	for (int i = 0; i < N; ++i) {
		vec[i] = dist(rng);
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	std::vector<unsigned int> v1(vec), v2(vec);
	radix_sort(v1);
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
