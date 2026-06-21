#pragma once

#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <cassert>
#include <stdexcept>

template<typename K, typename V>
class HashTable {
	private:
		using value_type = std::pair<K, V>;
		std::vector<std::list<value_type>> table;

		size_t current_size;
		double max_load_factor = 0.75;

		size_t get_index(const K& key) const {
			assert(table.size() > 0);
			return std::hash<K>{}(key) & (table.size() - 1);
		}

		void check_load_and_rehash() {
			if (current_size > max_load_factor * table.size()) {
				rehash(table.size() * 2);
			}
		}

		size_t power_of_2_policy(size_t new_size) const {
			size_t cap = 1;
			while (cap < new_size)
				cap <<= 1;
			return cap;
		};

	public:

		HashTable(size_t capacity = 8) : table(power_of_2_policy(capacity)), current_size(0) {}

		bool empty() const {
			return current_size == 0;
		}

		size_t size() const {
			return current_size;
		}

		void insert(const K& key, const V& value) {
			size_t index = get_index(key);
			for (auto& kv : table[index]) {
				if (kv.first == key) {
					kv.second = value;
					return;
				}
			}
			table[index].emplace_back(key, value);
			++current_size;
			check_load_and_rehash();
		}

		bool erase(const K& key) {
			size_t index = get_index(key);

			auto& bucket = table[index];
			for (auto it = bucket.begin(); it != bucket.end(); ++it) {
				if (it->first == key) {
					bucket.erase(it);
					--current_size;
					return true;
				}
			}
			return false;
		}

		V* find(const K& key) {
			size_t index = get_index(key);
			for (auto& kv : table[index]) {
				if (kv.first == key) {
					return &kv.second;
				}
			}
			return nullptr;
		}

		const V* find(const K& key) const {
			size_t index = get_index(key);
			for (const auto& kv : table[index]) {
				if (kv.first == key) {
					return &kv.second;
				}
			}
			return nullptr;
		}

		V& operator[](const K& key) {
			size_t index = get_index(key);
			for (auto& kv : table[index]) {
				if (kv.first == key) {
					return kv.second;
				}
			}
			table[index].emplace_back(key, V{});
			++current_size;
			check_load_and_rehash();
			index = get_index(key);
			return table[index].back().second;
		}

		const V& at(const K& key) const {
			size_t index = get_index(key);
			for (const auto& kv : table[index]) {
				if (kv.first == key) {
					return kv.second;
				}
			}
			throw std::out_of_range("Key not found in HashTable::at()");
		}

		V& at(const K& key) {
			return const_cast<V&>(static_cast<const HashTable*>(this)->at(key));
		}

		void rehash(size_t new_capacity) {
			size_t power_of_two = power_of_2_policy(new_capacity);
			std::vector<std::list<value_type>> new_table(power_of_two);
			for (auto& bucket : table) {
				for (auto& kv : bucket) {
					size_t new_index = std::hash<K>{}(kv.first) & (power_of_two - 1);
					new_table[new_index].push_back(kv);
				}
			}
			table = std::move(new_table);
		}

		void clear() {
			for (auto& bucket : table) {
				bucket.clear();
			}
			current_size = 0;
		}
};
