#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

int binary_search(const std::vector<int>& vec, int key, int l, int h) {
	if (l > h || key < vec[l] || key > vec[h])
		return -1;
	int mid  = l + (h - l) / 2;
	if (vec[mid] == key)
		return mid;
	if (vec[mid] < key)
		return binary_search(vec, key, mid + 1, h);
	else
		return binary_search(vec, key, l, mid - 1);
}

int exponential_search(const std::vector<int>& vec, int key) {
	if (vec.empty())
		return -1;
	if (vec[0] == key)
		return 0;
	int bound = 1;
	int n = vec.size();
	while (bound < n && vec[bound] < key) {
		bound <<= 1;
	}
	int low = bound / 2;
	int high = std::min(bound, n - 1);
	return binary_search(vec, key, low, high);
}

void benchmark_searches(const std::vector<int>& vec, int num_queries) {
	std::vector<int> queries(num_queries);
	for (int i = 0; i < num_queries; ++i)
		queries[i] = vec[rand() % vec.size()];

	auto start1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < num_queries; ++i)
		binary_search(vec, queries[i], 0, vec.size() - 1);
	auto end1 = std::chrono::high_resolution_clock::now();

	auto start3 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < num_queries; ++i)
		exponential_search(vec, queries[i]);
	auto end3 = std::chrono::high_resolution_clock::now();

	auto t_rec = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
	auto t_exp = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3).count();

	std::cout << "\n--- Benchmark (" << num_queries << " random queries) ---\n";
	std::cout << "Recursive Binary: " << t_rec << " ms\n";
	std::cout << "Exponential:      " << t_exp << " ms\n";
}

int main() {
	srand(time(0));
	const int N = 1'000'000;
	const int QUERIES = 1000000;
	std::vector<int> data(N);
	for (int i = 0; i < N; ++i)
		data[i] = rand();
	std::sort(data.begin(), data.end());
	benchmark_searches(data, QUERIES);
	return 0;
}
