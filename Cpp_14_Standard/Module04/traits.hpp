#pragma once

template<typename T>
struct is_integral {
	static constexpr bool value = false;
};

template<>
struct is_integral<int> {
	static constexpr bool value = true;
};

template<>
struct is_integral<char> {
	static constexpr bool value = true;
};

template<>
struct is_integral<short> {
	static constexpr bool value = true;
};

template<>
struct is_integral<long> {
	static constexpr bool value = true;
};

template<typename T>
struct is_floating_point {
	static constexpr bool value = false;
};

template<>
struct is_floating_point<float> {
	static constexpr bool value = true;
};

template<>
struct is_floating_point<double> {
	static constexpr bool value = true;
};

template<typename T>
struct is_arithmetic {
	static constexpr bool value = is_integral<T>::value || is_floating_point<T>::value;
};

template<typename T>
struct zero {
	static constexpr T value = T();
};

template<>
struct zero<float> {
	static constexpr float value = 0.0f;
};

template<>
struct zero<double> {
	static constexpr double value = 0.0;
};
