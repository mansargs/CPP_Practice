#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>

static void max_heapify(std::vector<int>& vec, int n, int idx) {
	int largest = idx;
	int left = 2 * idx + 1, right = 2 * (idx + 1);
	if (left < n && vec[left] > vec[largest])
		largest = left;
	if (right < n && vec[right] > vec[largest])
		largest = right;
	if (largest != idx) {
		std::swap(vec[idx], vec[largest]);
		max_heapify(vec, n, largest);
	}
}

void heap_sort(std::vector<int>& vec) {
	for (int i = vec.size() / 2 - 1; i >= 0; --i)
		max_heapify(vec, vec.size(), i);
	for (int n = vec.size() - 1; n >= 1; --n) {
		std::swap(vec[0], vec[n]);
		max_heapify(vec, n, 0);
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
	::heap_sort(v1);
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
