#include <iostream>
#include <iterator>
#include <random>
#include <algorithm>
#include <vector>

static void insertion_sort(std::vector<float>& vec) {
	for (size_t i = 1; i < vec.size(); ++i) {
		float temp = vec[i];
		int j = i - 1;
		for (; j >= 0; --j) {
			if (vec[j] > temp)
				vec[j + 1] = vec[j];
			else
				break;
		}
		vec[j + 1] = temp;
	}
}

void bucket_sort(std::vector<float>& vec) {
	size_t n = vec.size();
	std::vector<std::vector<float>> bucket(n);

	for (size_t i = 0;  i < n; ++i)
		bucket[vec[i] * n].push_back(vec[i]);
	for (size_t i = 0; i < n; ++i) {
		if (!bucket[i].empty())
			insertion_sort(bucket[i]);
	}
	int k = 0;
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < bucket[i].size(); ++j)
			vec[k++] = bucket[i][j];
	}
}

int main() {
	static const int N = 10;
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	std::vector<float> vec(N);
	std::cout << "Unsorted vector\n";
	for (int i = 0; i < N; ++i) {
		vec[i] = dist(rng);
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	std::vector<float> v1(vec), v2(vec);
	bucket_sort(v1);
	std::cout << "\nSorted vector\n";
	copy(v1.begin(), v1.end(), std::ostream_iterator<float>(std::cout, " "));
	std::cout << std::endl;
	std::sort(v2.begin(), v2.end());
	if (v1 == v2)
		std::cout << "OK\n";
	else
		std::cout << "KO\n";
	return 0;
}
