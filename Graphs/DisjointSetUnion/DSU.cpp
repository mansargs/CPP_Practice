#include "DSU.hpp"

DSU::DSU(int n) {
	rank.resize(n, 0);
	parent.resize(n);
	for (int i = 0; i < n; ++i)
		parent[i] = i;
}

int DSU::find(int x) {
	if (x != parent[x])
		parent[x] = find(parent[x]);
	return parent[x];
}

bool DSU::sameSet(int x, int y) {
	return find(x) == find(y);
}

void DSU::unite(int x, int y) {
	int root_x = find(x);
	int root_y = find(y);
	if(root_x == root_y)
		return ;
	if (rank[root_x] < rank[root_y])
		parent[root_x] = root_y;
	else if (rank[root_x] > rank[root_y])
		parent[root_y] = root_x;
	else {
		parent[root_y] = root_x;
		rank[root_x]++;
	}
}
