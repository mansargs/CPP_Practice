#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

int partition(std::vector<int>& vec, int l, int h) {
	int pivot = vec[l + (h - l) / 2];
	int i = l, j = h;
	while (true) {
		while (vec[i] < pivot) ++i;
		while (vec[j] > pivot) --j;
		if (i >= j)
			break;
		std::swap(vec[i++], vec[j--]);
	}
	return j;
}

void quick_sort(std::vector<int>& vec, int l, int h) {
	while (l < h) {
		int p = partition(vec, l, h);
		if (p - l < h - p) {
			quick_sort(vec, l, p);
			l = p + 1;
		} else {
			quick_sort(vec, p + 1, h);
			h = p;
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
	quick_sort(v1, 0, v1.size() - 1);
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
