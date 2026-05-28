#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

int interpolation_search(const std::vector<int>& vec, int key) {
	int low = 0;
	int high = vec.size() - 1;

	while (low <= high && key >= vec[low] && key <= vec[high]) {
		if (vec[low] == vec[high]) {
			if (vec[low] == key)
				return low;
			else
				break;
		}
		int pos = low + (double)(key - vec[low]) * (high - low) / (vec[high] - vec[low]);
		if (pos < low || pos > high)
			break;
		if (vec[pos] == key)
			return pos;
		else if (vec[pos] < key)
			low = pos + 1;
		else
			high = pos - 1;
	}
	return -1;
}

int binary_search_custom(const std::vector<int>& vec, int key) {
	int low = 0, high = vec.size() - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (vec[mid] == key)
			return mid;
		else if (vec[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

void benchmark(const std::vector<int>& v, const std::string& label) {
	const int TESTS = 100000;

	auto start1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < TESTS; ++i) {
		int idx = rand() % v.size();
		int key = v[idx];
		interpolation_search(v, key);
	}
	auto end1 = std::chrono::high_resolution_clock::now();

	auto start2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < TESTS; ++i) {
		int idx = rand() % v.size();
		int key = v[idx];
		binary_search_custom(v, key);
	}
	auto end2 = std::chrono::high_resolution_clock::now();

	auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
	auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

	std::cout << "\n=== " << label << " ===\n";
	std::cout << "Interpolation: " << t1 << " ms\n";
	std::cout << "Binary:        " << t2 << " ms\n";
}

int main() {
	srand(time(0));
	const int N = 1'000'000;
	std::vector<int> random_numbers(N);
	for (int i = 0; i < N; ++i)
		random_numbers[i] = rand();
	std::sort(random_numbers.begin(), random_numbers.end());
	benchmark(random_numbers, "Random Data");
	return 0;
}
