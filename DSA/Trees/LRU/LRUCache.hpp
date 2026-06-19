#pragma once

#include <unordered_map>
#include <list>
#include <optional>

template<typename Key, typename Value>
class LRUCache {
	private:
		size_t capacity;
		std::list<std::pair<Key, Value>> dll;
		std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> umap;
	public:
		LRUCache(size_t capacity) {
			this->capacity = capacity;
		}

		std::optional<Value> get(Key key) {
			if (umap.find(key) == umap.end())
				return std::nullopt;
			dll.splice(dll.begin(), dll, umap[key]);
			return umap[key]->second;
		}

		void put(Key key, Value value) {
			if (get(key) != std::nullopt) {
				umap[key]->second = value;
				return ;
			}
			if (dll.size() == capacity) {
				Key last_key = dll.back().first;
				dll.pop_back();
				umap.erase(last_key);
			}
			dll.push_front({key, value});
			umap[key] = dll.begin();
		}
};
