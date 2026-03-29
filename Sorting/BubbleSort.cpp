#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

void bubble_sort(std::vector<int>& vec) {
	size_t n = vec.size();

	for (size_t i = 0; i + 1 < n; ++i) {
		bool updated = false;
		for (size_t j = 0; j + 1 < n - i; ++j) {
			if (vec[j] > vec[j + 1]) {
				std::swap(vec[j], vec[j + 1]);
				updated = true;
			}
		}
		if (!updated)
			break;
	}
}

int main () {
	static const int N = 1000;
	std::vector<int> vec(N);
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution dist(-100000, 100000);

	for (size_t i = 0; i < N; ++i)
		vec[i] = dist(rng);

	std::vector<int> v1(vec), v2(vec);
	bubble_sort(v1);
	std::sort(v2.begin(), v2.end());
	if (v1 == v2)
		std::cout << "Vectors are equal\n";
	else
		std::cout << "Vectors aren't equal\n";
	return 0;
}
