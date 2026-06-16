#include "Vec2.hpp"

int main() {
	Vec2 a{0, 0};
	Vec2 b{10, 20};
	Vec2 mid = lerp(a, b, 0.5);
	print(mid);
	int x = 5;
	print(x);
	return 0;
}
