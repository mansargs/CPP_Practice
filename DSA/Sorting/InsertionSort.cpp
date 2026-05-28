#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

void insertion_sort(std::vector<int>& vec) {
	int n = vec.size();

	for (int i = 1; i < n; ++i) {
		int key = vec[i];
		int j = i - 1;
		for ( ; j >= 0 && vec[j] > key; --j)
			vec[j + 1] = vec[j];
		vec[j + 1] = key;
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
	insertion_sort(v1);
	std::sort(v2.begin(), v2.end());
	if (v1 == v2)
		std::cout << "Vectors are equal\n";
	else
		std::cout << "Vectors aren't equal\n";
	return 0;
}
