#ifndef DSU_HPP
# define DSU_HPP

#include <vector>

class DSU {
	private:
		std::vector<int> rank;
		std::vector<int> parent;
	public:
		DSU(int n);
		int find(int x);
		void unite(int x, int y);
		bool sameSet(int x, int y);
};

#endif
