#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

static void merge(std::vector<int>& vec, int l, int mid, int h) {
	std::vector<int> v1(vec.begin() + l, vec.begin() + mid + 1);
	std::vector<int> v2(vec.begin() + mid + 1, vec.begin() + h + 1);

	int i = 0, j = 0, k = l;

	while (i < v1.size() && j < v2.size()) {
		if (v1[i] < v2[j]) {
			vec[k] = v1[i];
			++i;
		}
		else {
			vec[k] = v2[j];
			++j;
		}
		++k;
	}
	while (i < v1.size()) {
		vec[k] = v1[i];
		++i; ++k;
	}
	while (j < v2.size()) {
		vec[k] = v2[j];
		++j; ++k;
	}
}

void merge_sort(std::vector<int>& vec, int l, int h) {
	if (l < h) {
		int mid = l + (h - l) / 2;
		merge_sort(vec, l, mid);
		merge_sort(vec, mid + 1, h);
		merge(vec, l, mid, h);
	}
}

#include <iterator>

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
	merge_sort(v1, 0, v1.size() - 1);
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
