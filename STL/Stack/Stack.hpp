#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T>
class Stack {
	private:
		T* data;
		size_t _sz;
		size_t capacity;

		void grow() {
			capacity *= 2;
			T* new_data = new T[capacity];
			for (size_t i = 0; i <_sz; ++i)
				new_data[i] = data[i];
			delete[] data;
			data = new_data;
		}

	public:

		Stack(size_t init_cap = 4) : _sz(0), capacity(init_cap) {
			data = new T[capacity];
		}

		Stack(const Stack& oth) : _sz(oth._sz), capacity(oth.capacity) {
			data = new T[capacity];
			for (size_t i = 0; i < _sz; ++i)
				data[i] = oth.data[i];
		}

		Stack(Stack&& oth) noexcept : data(oth.data),_sz(oth._sz), capacity(oth.capacity) {
			oth.data = nullptr;
			oth._sz = 0;
			oth.capacity = 0;
		}

		Stack& operator=(const Stack& oth) {
			if (this == &oth)
				return *this;
			delete[] data;
			_sz = oth._sz;
			capacity = oth.capacity;
			data = new T[capacity];
			for (size_t i = 0; i < _sz; ++i)
				data[i] = oth.data[i];
			return *this;
		}

		Stack& operator=(Stack&& oth) noexcept {
			if (this == &oth)
				return *this;
			_sz = oth._sz;
			capacity = oth.capacity;
			data = oth.data;
			oth._sz = 0;
			oth.capacity = 0;
			oth.data = nullptr;
			return *this;
		}

		~Stack() {
			delete[] data;
		}

		void push(const T& value) {
			if (_sz == capacity)
				grow();
			data[_sz++] = value;
		}

		void pop() {
			if (empty())
				throw std::runtime_error("Stack is empty");
			data[--_sz].~T();
		}

		T& top() {
			if (empty())
				throw std::runtime_error("Stack is empty");
			return data[_sz - 1];
		}

		const T& top() const {
			if (empty())
				throw std::runtime_error("Stack is empty");
			return data[_sz - 1];
		}

		bool empty() const {
			return _sz == 0;
		}

		size_t size() const {
			return _sz;
		}
};
