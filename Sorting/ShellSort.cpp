#include <algorithm>
#include <iostream>
#include <random>
#include <iterator>
#include <vector>

void shell_sort(std::vector<int>& vec) {
	int n = vec.size();
	for (int gap = n / 2; gap >= 1; gap /= 2) {
		for (int i = gap; i < n; ++i) {
			int temp = vec[i];
			int j = i;
			for (; j >= gap && vec[j - gap] > temp; j -= gap)
				vec[j] = vec[j - gap];
			vec[j] = temp;
		}
	}
}

int main() {
	static const int N = 10;
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution dist(-1000, 1000);

	std::vector<int> vec(N);
	std::cout << "Unsorted vector\n";
	for (int i = 0; i < N; ++i) {
		vec[i] = dist(rng);
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	std::vector<int> v1(vec), v2(vec);
	shell_sort(v1);
	std::cout << "\nSorted vector\n";
	copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	std::sort(v2.begin(), v2.end());
	if (v1 == v2)
		std::cout << "OK\n";
	else
		std::cout << "KO\n";
	return 0;
}
