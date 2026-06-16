#pragma once

#include "VecConcepts.hpp"

struct Vec2 {
	double x, y;

	Vec2 operator+(const Vec2& other) const {
		return {x + other.x, y + other.y};
	}

	Vec2 operator-(const Vec2& other) const {
		return {x - other.x, y - other.y};
	}

	Vec2 operator*(double s) const {
		return {x * s, y * s};
	}

	Vec2 operator/(double s) const {
		return {x / s, y / s};
	}

	friend Vec2 operator*(double s, const Vec2& v) {
		return v * s;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
		return os << "(" << v.x << ", " << v.y << ")";
	}
};
