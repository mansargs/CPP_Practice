#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

std::vector<int>::const_iterator binary_search_iter(const std::vector<int>& arr, int key) {
	auto l = arr.begin();
	auto h = arr.end();
	std::vector<int>::const_iterator mid;

	while (l < h) {
		mid = l + (h - l) / 2;
		if (*mid == key)
			return mid;
		if (*mid > key)
			h = mid;
		else
			l = mid + 1;
	}
	return arr.end();
}

size_t binary_search_rec(const std::vector<int>& arr, int key, int l, int h) {
	if (l > h)
		return arr.size();
	size_t mid = l + (h - l) / 2;
	if (arr[mid] == key)
		return mid;
	else if (arr[mid] < key)
		return binary_search_rec(arr, key, mid + 1, h);
	else
		return binary_search_rec(arr, key, l, mid - 1);
}

void benchmark(const std::vector<int>& arr, int tests) {
	std::vector<int> queries(tests);
	for (int i = 0; i < tests; ++i)
		queries[i] = arr[rand() % arr.size()];

	auto start1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < tests; ++i)
		binary_search_iter(arr, queries[i]);
	auto end1 = std::chrono::high_resolution_clock::now();

	auto start2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < tests; ++i)
		binary_search_rec(arr, queries[i], 0, arr.size() - 1);
	auto end2 = std::chrono::high_resolution_clock::now();

	auto t_iter = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
	auto t_rec = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

	std::cout << "Binary Search Benchmark (" << tests << " queries)\n";
	std::cout << "Iterative: " << t_iter << " ms\n";
	std::cout << "Recursive: " << t_rec << " ms\n";
}

int main() {
	srand(time(0));
	const int N = 1'000'000;
	const int TESTS = 1000000;

	std::vector<int> arr(N);
	for (int i = 0; i < N; ++i)
		arr[i] = rand();
	std::sort(arr.begin(), arr.end());
	benchmark(arr, TESTS);
	return 0;
}
