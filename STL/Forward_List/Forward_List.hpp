#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class Forward_List {
	private:
		struct Node {
			T value;
			Node* next;

			Node(const T& v) : value(v), next(nullptr) {}
		};

		Node* head;

	public:
		class Iterator {
			private:
				Node* current;

			public:
				using iterator_category = std::forward_iterator_tag;
				using value_type = T;
				using difference_type = std::ptrdiff_t;
				using pointer = T*;
				using reference = T&;

				Iterator(Node* ptr) : current(ptr) {}

				reference operator*() const { return current->value; }
				pointer operator->() const { return &current->value; }

				Iterator& operator++() {
					if (current) current = current->next;
					return *this;
				}

				Iterator operator++(int) {
					Iterator tmp = *this;
					++(*this);
					return tmp;
				}

				bool operator==(const Iterator& other) const {
					return current == other.current;
				}

				bool operator!=(const Iterator& other) const {
					return current != other.current;
				}

				friend class Forward_List;
		};

		class ConstIterator {
			private:
				const Node* current;

			public:
				using iterator_category = std::forward_iterator_tag;
				using value_type = T;
				using difference_type = std::ptrdiff_t;
				using pointer = const T*;
				using reference = const T&;

				ConstIterator(const Node* ptr) : current(ptr) {}

				reference operator*() const { return current->value; }
				pointer operator->() const { return &current->value; }

				ConstIterator& operator++() {
					if (current)
						current = current->next;
					return *this;
				}

				ConstIterator operator++(int) {
					ConstIterator tmp = *this;
					++(*this);
					return tmp;
				}

				bool operator==(const ConstIterator& other) const {
					return current == other.current;
				}

				bool operator!=(const ConstIterator& other) const {
					return current != other.current;
				}
		};

		Forward_List() : head(nullptr) {}

		Forward_List(std::initializer_list<T> init) : head(nullptr) {
			for (const T& val : init)
				push_back(val);
		}

		Forward_List(const Forward_List& other) : head(nullptr) {
			Node* curr = other.head;
			while (curr) {
				push_back(curr->value);
				curr = curr->next;
			}
		}

		Forward_List& operator=(const Forward_List& other) {
			if (this == &other)
				return *this;
			clear();
			Node* curr = other.head;
			while (curr) {
				push_back(curr->value);
				curr = curr->next;
			}
			return *this;
		}

		~Forward_List() {
			clear();
		}

		void push_front(const T& val) {
			Node* new_node = new Node(val);
			new_node->next = head;
			head = new_node;
		}

		void push_back(const T& val) {
			Node* new_node = new Node(val);
			if (!head) {
				head = new_node;
				return;
			}
			Node* curr = head;
			while (curr->next)
				curr = curr->next;
			curr->next = new_node;
		}

		void pop_front() {
			if (!head)
				return;
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}

		void pop_back() {
			if (!head)
				return;
			if (!head->next) {
				delete head;
				head = nullptr;
				return;
			}
			Node* curr = head;
			while (curr->next->next)
				curr = curr->next;
			delete curr->next;
			curr->next = nullptr;
		}

		void clear() {
			while (head)
				pop_front();
		}

		bool search(const T& val) const {
			Node* curr = head;
			while (curr) {
				if (curr->value == val)
					return true;
				curr = curr->next;
			}
			return false;
		}

		Iterator find(const T& val) {
			Node* curr = head;
			while (curr) {
				if (curr->value == val)
					return Iterator(curr);
				curr = curr->next;
			}
			return end();
		}

		ConstIterator find(const T& val) const {
			const Node* curr = head;
			while (curr) {
				if (curr->value == val)
					return ConstIterator(curr);
				curr = curr->next;
			}
			return end();
		}

		Iterator insert_after(Iterator it, const T& val) {
			if (it.current == nullptr)
				return end();
			Node* new_node = new Node(val);
			new_node->next = it.current->next;
			it.current->next = new_node;
			return Iterator(new_node);
		}

		//optional std::forward_list not support
		size_t size() const {
			size_t count = 0;
			Node* curr = head;
			while (curr) {
				++count;
				curr = curr->next;
			}
			return count;
		}

		Iterator begin() { return Iterator(head); }
		Iterator end() { return Iterator(nullptr); }

		ConstIterator begin() const { return ConstIterator(head); }
		ConstIterator end() const { return ConstIterator(nullptr); }
};
