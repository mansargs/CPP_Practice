#pragma once

#include <vector>
#include <stdexcept>
#include <functional>

template<typename T, typename Compare = std::less<T>>
class PriorityQueue {
	private:
		std::vector<T> heap;

	public:
		PriorityQueue() = default;

		void push(const T& value);
		void pop();
		const T& top() const;
		bool empty() const;
		size_t size() const;

	private:

		void heapify_up(size_t index);
		void heapify_down(size_t index);
};

template<typename T, typename Compare>
const T& PriorityQueue<T, Compare>::top() const {
	if (heap.empty())
		throw std::out_of_range("PriorityQueue is empty");
	return heap[0];
}

template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::empty() const {
	return heap.size() == 0;
}

template<typename T, typename Compare>
size_t PriorityQueue<T, Compare>::size() const {
	return heap.size();
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::heapify_up(size_t index) {
	Compare comp;

	while (index > 0) {
		size_t parent = (index - 1) / 2;
		if (!comp(heap[parent], heap[index]))
			break;
		std::swap(heap[parent], heap[index]);
		index = parent;
	}
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::heapify_down(size_t index) {
	Compare comp;
	size_t n = heap.size();

	while (true) {
		size_t best = index,
			   l = index * 2 + 1,
			   r = index * 2 + 2;
		if (l < n && comp(heap[best], heap[l]))
			best = l;
		if (r < n && comp(heap[best], heap[r]))
			best = r;
		if (index == best)
			break;
		std::swap(heap[best], heap[index]);
		index = best;
	}
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T& value) {
	heap.push_back(value);
	heapify_up(heap.size() - 1);
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::pop() {
	if (heap.empty())
		throw std::out_of_range("empty");
	std::swap(heap[0], heap[heap.size() - 1]);
	heap.pop_back();
	if (!heap.empty())
		heapify_down(0);
}
