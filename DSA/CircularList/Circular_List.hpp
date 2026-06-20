#pragma once
#include <cstddef>
#include <initializer_list>

template<typename T>
class Circular_List {
	private:
		struct Node {
			T value;
			Node* next;

			Node(const T& v) : value(v), next(nullptr) {}
		};

		Node* head;
		Node* tail;
		size_t len;

		void clear() {
			if (!head)
				return;
			Node* curr = head;
			do {
				Node* tmp = curr;
				curr = curr->next;
				delete tmp;
			} while (curr != head);
			head = tail = nullptr;
			len = 0;
		}

	public:

		Circular_List() : head(nullptr), tail(nullptr), len(0) {}

		Circular_List(std::initializer_list<T> init) : head(nullptr), tail(nullptr), len(0) {
			for (const T& v : init) {
				push_back(v);
			}
		}

		Circular_List(const Circular_List& oth) : head(nullptr), tail(nullptr), len(0) {
			if (!oth.head)
				return;
			Node* curr = oth.head;
			do {
				push_back(curr->value);
				curr = curr->next;
			} while (curr != oth.head);
		}

		Circular_List(Circular_List&& oth) noexcept : head(oth.head), tail(oth.tail), len(oth.len) {
			oth.head = nullptr;
			oth.tail = nullptr;
			oth.len = 0;
		}

		~Circular_List() {
			clear();
		}

		Circular_List& operator=(const Circular_List& oth) {
			if (this == &oth)
				return *this;
			clear();
			if (!oth.head)
				return *this;
			Node* curr = oth.head;
			do {
				push_back(curr->value);
				curr = curr->next;
			} while (curr != oth.head);
			return *this;
		}

		Circular_List& operator=(Circular_List&& oth) noexcept {
			if (this == &oth)
				return *this;
			clear();
			head = oth.head;
			tail = oth.tail;
			len = oth.len;
			oth.head = oth.tail = nullptr;
			oth.len = 0;
			return *this;
		}

		size_t size() const {
			return len;
		}

		bool empty() const {
			return len == 0;
		}

		T& front() {
			return head->value;
		}

		T& back() {
			return tail->value;
		}

		const T& front() const {
			return head->value;
		}

		const T& back() const {
			return tail->value;
		}

		void push_front(const T& val) {
			Node* node = new Node(val);
			if (!head) {
				head = tail = node;
				node->next = node;
			} else {
				node->next = head;
				tail->next = node;
				head = node;
			}
			++len;
		}

		void push_back(const T& val) {
			Node* node = new Node(val);
			if (!head) {
				head = tail = node;
				node->next = node;
			} else {
				node->next = head;
				tail->next = node;
				tail = node;
			}
			++len;
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
			tail->next = head;
			delete old;
			--len;
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
			Node* curr = head;
			while (curr->next != tail) {
				curr = curr->next;
			}
			delete tail;
			tail = curr;
			tail->next = head;
			--len;
		}
};
