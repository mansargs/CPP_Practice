#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T, typename Comp = std::less<T>>
class Heap {
	private:
		std::vector<T> tree;
		Comp cmp;

		void sift_up(int index) {
			while (index > 0) {
				int parent = (index - 1) / 2;
				if (!cmp(tree[index], tree[parent]))
					break;
				std::swap(tree[index], tree[parent]);
				index = parent;
			}
		}

		void sift_down(int index) {
			while (true) {
				int best = index, left = 2 * index + 1, right = 2 * index + 2;
				if (left < tree.size() && cmp(tree[left], tree[best]))
					best = left;
				if (right < tree.size() && cmp(tree[right], tree[best]))
					best = right;
				if (best == index)
					break;
				std::swap(tree[index], tree[best]);
				index = best;
			}
		}
	public:
		const T& top() const {
			if (tree.empty())
				std::out_of_range("Tree is empty");
			return tree[0];
		}

		bool empty() const {
			return tree.empty();
		}

		size_t size() const {
			return tree.size();
		}

		void pop() {
			if (tree.empty())
				return ;
			std::swap(tree.front(), tree.back());
			tree.pop_back();
			if (!tree.empty())
				sift_down(0);
		}

		void insert(const T& value) {
			tree.push_back(value);
			sift_up(tree.size() - 1);
		}

		void heapify() {
			if (tree.empty())
				return ;
			for (int i = tree.size() / 2; i >=0; --i)
				sift_down(i);
		}

		void remove(const T& value) {
			auto it = std::find(tree.begin(), tree.end(), value);
			if (it == tree.end())
				return ;
			int i = it - tree.begin();
			std::swap(tree[i], tree.back());
			tree.pop_back();
			if (i < tree.size()) {
				sift_up(i);
				sift_down(i);
			}
		}
};

