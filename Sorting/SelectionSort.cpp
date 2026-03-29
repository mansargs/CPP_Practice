#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

void selection_sort(std::vector<int>& vec) {
	int n = vec.size();
	for (int i = 0; i < n - 1; ++i) {
		int min = i;
		for (int j = i + 1; j < n; ++j) {
			if (vec[j] < vec[min])
				min = j;
		}
		if (min != i)
			std::swap(vec[min], vec[i]);
	}
}

int main() {
	static const int N = 10000;
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution dist(-1000, 1000);

	std::vector<int> vec(N);
	for (int i = 0; i < N; ++i)
		vec[i] = dist(rng);

	std::vector<int> v1(vec), v2(vec);
	selection_sort(v1);
	std::sort(v2.begin(), v2.end());
	if (v1 == v2)
		std::cout << "OK\n";
	else
		std::cout << "KO\n";
	return 0;
}
