#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>

template<typename T>
class List {
	private:
		struct Node {
			Node* next;
			Node* prev;
			T val;

			Node(const T& v) : next(nullptr), prev(nullptr), val(v) {}
		};

		Node* head;
		Node* tail;
		size_t len;

	public:

		class Iterator {
			private:
				Node* current;

			public:
				using iterator_category = std::bidirectional_iterator_tag;
				using value_type        = T;
				using difference_type   = std::ptrdiff_t;
				using pointer           = T*;
				using reference         = T&;

				Iterator(Node* n = nullptr) : current(n) {}

				reference operator*() {
					return current->val;
				}

				pointer operator->() {
					return &current->val;
				}

				const T& operator*() const {
					return current->val;
				}

				const T* operator->() const {
					return &current->val;
				}

				Iterator& operator++() {
					current = current->next;
					return *this;
				}

				Iterator operator++(int) {
					Iterator tmp = *this;
					current = current->next;
					return tmp;
				}

				Iterator& operator--() {
					current = current->prev;
					return *this;
				}

				Iterator operator--(int) {
					Iterator tmp = *this;
					current = current->prev;
					return tmp;
				}

				bool operator==(const Iterator& other) const {
					return current == other.current;
				}

				bool operator!=(const Iterator& other) const {
					return current != other.current;
				}

				friend class List;
		};

	public:

		List() : head(nullptr), tail(nullptr), len(0) {}

		List(std::initializer_list<T> init) : head(nullptr), tail(nullptr), len(0) {
			for (const T& v : init)
				push_back(v);
		}

		~List() {
			clear();
		}

		List(const List& other) : head(nullptr), tail(nullptr), len(0) {
			for (Node* curr = other.head; curr; curr = curr->next)
				push_back(curr->val);
		}

		List(List&& other) noexcept
			: head(other.head), tail(other.tail), len(other.len) {
			other.head = nullptr;
			other.tail = nullptr;
			other.len = 0;
		}

		List& operator=(const List& other) {
			if (this == &other)
				return *this;
			clear();
			for (Node* curr = other.head; curr; curr = curr->next)
				push_back(curr->val);
			return *this;
		}

		List& operator=(List&& other) noexcept {
			if (this == &other)
				return *this;
			clear();
			head = other.head;
			tail = other.tail;
			len  = other.len;
			other.head = nullptr;
			other.tail = nullptr;
			other.len = 0;
			return *this;
		}

		void clear() {
			Node* curr = head;
			while (curr) {
				Node* next = curr->next;
				delete curr;
				curr = next;
			}
			head = tail = nullptr;
			len = 0;
		}

		size_t size() const {
			return len;
		}

		bool empty() const {
			return len == 0;
		}

		void push_back(const T& val) {
			Node* node = new Node(val);
			if (!head) {
				head = tail = node;
			} else {
				tail->next = node;
				node->prev = tail;
				tail = node;
			}
			++len;
		}

		void push_front(const T& val) {
			Node* node = new Node(val);
			if (!head) {
				head = tail = node;
			} else {
				node->next = head;
				head->prev = node;
				head = node;
			}
			++len;
		}

		void pop_back() {
			if (!head)
				return;
			if (len == 1) {
				delete head;
				head = tail = nullptr;
				len = 0;
				return;
			}
			Node* old = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete old;
			--len;
		}

		void pop_front() {
			if (!head)
				return;
			if (len == 1) {
				delete head;
				head = tail = nullptr;
				len = 0;
				return;
			}
			Node* old = head;
			head = head->next;
			head->prev = nullptr;
			delete old;
			--len;
		}

		Iterator begin() {
			return Iterator(head);
		}

		Iterator end() {
			return Iterator(nullptr);
		}

		Iterator begin() const {
			return Iterator(head);
		}

		Iterator end() const {
			return Iterator(nullptr);
		}
};
