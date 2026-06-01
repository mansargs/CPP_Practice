#pragma once

template<typename Derived>
class Shape {
	public:
		double area() const {
			return static_cast<const Derived*>(this)->area();
		}

		void print() const {
			static_cast<const Derived*>(this)->print();
		}
};
