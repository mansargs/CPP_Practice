#pragma once

#include <concepts>
#include <iostream>

template<typename T>
concept Addable = requires(T a, T b) {
	{a + b} -> std::same_as<T>;
	{a - b} -> std::same_as<T>;
};

template<typename T>
concept Scalable = requires(T a, double s) {
	{a * s} -> std::same_as<T>;
	{s * a} -> std::same_as<T>;
	{a / s} -> std::same_as<T>;
};

template<typename T>
concept VectorSpace = Addable<T> && Scalable<T>;

template<typename T>
concept Printable = requires(T a, std::ostream& os) {
	{os << a} -> std::same_as<std::ostream&>;
};

template<Printable T>
void print(const T& value) {
	std::cout << value << std::endl;
};

template<VectorSpace T>
T lerp(const T& a, const T& b, double t) {
    return a + (b - a) * t;
};
