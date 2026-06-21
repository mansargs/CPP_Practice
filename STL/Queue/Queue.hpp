#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T>
class Queue {
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

		Queue(size_t init_cap = 4) : _sz(0), capacity(init_cap) {
			data = new T[capacity];
		}

		Queue(const Queue& oth) : _sz(oth._sz), capacity(oth.capacity) {
			data = new T[capacity];
			for (size_t i = 0; i < _sz; ++i)
				data[i] = oth.data[i];
		}

		Queue(Queue&& oth) noexcept : data(oth.data),_sz(oth._sz), capacity(oth.capacity) {
			oth.data = nullptr;
			oth._sz = 0;
			oth.capacity = 0;
		}

		Queue& operator=(const Queue& oth) {
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

		Queue& operator=(Queue&& oth) noexcept {
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

		~Queue() {
			delete[] data;
		}

		void clear() {
			for (size_t i = 0; i < _sz; ++i)
				data[i].~T();
			_sz = 0;
		}

		void push(const T& value) {
			if (_sz == capacity)
				grow();
			data[_sz++] = value;
		}

		void pop() {
			if (empty())
				throw std::runtime_error("Queue is empty");
			for(size_t i = 1; i < _sz; ++i)
				data[i - 1] = data[i];
			--_sz;
		}

		T& back() {
			if (empty())
				throw std::runtime_error("Queue is empty");
			return data[_sz - 1];
		}

		const T& back() const {
			if (empty())
				throw std::runtime_error("Queue is empty");
			return data[_sz - 1];
		}

		T& front() {
			if (empty())
				throw std::runtime_error("Queue is empty");
			return data[0];
		}

		const T& front() const {
			if (empty())
				throw std::runtime_error("Queue is empty");
			return data[0];
		}

		bool empty() const {
			return _sz == 0;
		}

		size_t size() const {
			return _sz;
		}
};
