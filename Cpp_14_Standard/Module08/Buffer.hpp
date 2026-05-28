#pragma once

#include <utility>
#include <iostream>

class Buffer {
	private:
		int* data;
		size_t size;
	public:
		Buffer(size_t s) : data(new int[s]), size(s) {
			std::cout << "Contrsuted\n";
		}

		~Buffer() {
			delete[] data;
			std::cout << "Destroyed\n";
		}

		Buffer(const Buffer& buf) = delete;
		Buffer& operator=(const Buffer& buf) = delete;

		Buffer(Buffer&& oth) noexcept : data(std::exchange(oth.data, nullptr)),
										size(std::exchange(oth.size, 0)) {
			std::cout << "Move constructed\n";
		}

		Buffer& operator=(Buffer&& oth) noexcept {
			if (this != &oth) {
				delete[] data;
				data = std::exchange(oth.data, nullptr);
				size = std::exchange(oth.size, 0);
				std::cout << "Move assigned\n";
			}
			return *this;
		}

		void print() const {
			std::cout << "Buffer size = " << size << std::endl;
		}
};
