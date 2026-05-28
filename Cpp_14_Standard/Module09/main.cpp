#include <iostream>
#include <cstdint>

constexpr bool has_flag(uint32_t reg, uint32_t flag) {
	return (reg & flag) != 0;
}

constexpr uint32_t set_flag(uint32_t reg, uint32_t flag) {
	return reg | flag;
}

constexpr uint32_t clear_flag(uint32_t reg, uint32_t flag) {
	return reg & ~flag;
}

int main () {
	constexpr uint32_t FLAG_A = 0b0000'0000'0000'0000'0000'0000'0000'0001;
	constexpr uint32_t FLAG_B = 0b0000'0000'0000'0000'0000'0000'0000'0010;
	constexpr uint32_t reg1 = set_flag(0, FLAG_A);
	static_assert(reg1 == FLAG_A, "FLAG_A should be set");
	constexpr uint32_t reg2 = set_flag(reg1, FLAG_B);
	static_assert(has_flag(reg2, FLAG_A), "FLAG_A still set");
	static_assert(has_flag(reg2, FLAG_B), "FLAG_B set");
	constexpr uint32_t reg3 = clear_flag(reg2, FLAG_A);
	static_assert(!has_flag(reg3, FLAG_A), "FLAG_A cleared");
	static_assert(has_flag(reg3, FLAG_B), "FLAG_B still set");
	std::cout << "Finish\n";
}
