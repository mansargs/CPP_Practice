#include <iostream>
#include <algorithm>
#include <array>

constexpr int fibonacci(int num) {
	if (num < 0)
		return -1;
	if (num == 0)
		return 0;
	if (num == 1)
		return 1;
	int first = 0;
	int second = 1;
	for (int i = 2; i <= num; ++i) {
		int next = first + second;
		first = second;
		second = next;
	}
	return second;
}

template<size_t N>
std::array<int, N + 1> fibonacci() {
	std::array<int, N + 1> fib{};
	fib[0] = 0;
	if (N > 0)
		fib[1] = 1;
	for (size_t i = 2; i <= N; ++i) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib;
}

int main() {
	std::cout << fibonacci(10) << std::endl;
	auto fib = fibonacci<10>();
	std::for_each(fib.begin(), fib.end(), [](int n) {
		std::cout << n << ' ';
	});
	std::cout << std::endl;
}
