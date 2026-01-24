#ifndef CONTROL_BLOCK_HPP
# define CONTROL_BLOCK_HPP

# include "Deleter.hpp"
# include <atomic>

template<typename T, typename Deleter = DefaultDeleter<T>>
class ControlBlock {
	T* data;
	std::atomic<size_t> strong_count;
	std::atomic<size_t> weak_count;
	Deleter deleter;

	ControlBlock(T* p, Deleter d = Deleter()) : data(p), strong_count(1),
		weak_count(0), deleter(d) {}
};

#endif

