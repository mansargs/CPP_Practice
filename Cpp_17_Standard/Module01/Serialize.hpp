#pragma once

#include <type_traits>
#include <iostream>
#include <string>
#include <utility>

template<typename T>
class is_string_convertable {
	private:
		template<typename U>
		static auto test(int) -> decltype(std::declval<U>().to_string(), std::true_type{});

		template<typename>
		static std::false_type test(...);

	public:
		static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
void serialize(const T& obj) {
	if constexpr (std::is_integral_v<T>)
		std::cout << obj;
	else if constexpr (std::is_floating_point_v<T>)
		std::cout << obj;
	else if constexpr (std::is_same_v<T, std::string>)
		std::cout << obj;
	else if constexpr (std::is_convertible_v<T, const char*>)
		std::cout << obj;
	else if constexpr (is_string_convertable<T>::value)
		std::cout << obj.to_string();
	else
		std::cout << "No valid way to print";
}
