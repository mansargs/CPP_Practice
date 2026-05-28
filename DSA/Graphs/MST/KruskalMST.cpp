#include <iostream>
#include <algorithm>
#include <vector>
#include "../DisjointSetUnion/DSU.hpp"

struct Edge {
	int u, v, w;
	bool operator<(const Edge& oth) const {
		return w < oth.w;
	}
};

void kruskal_mst(int num_vertices, std::vector<Edge> edges) {
	std::sort(edges.begin(), edges.end());
	DSU dsu(num_vertices);
	int mst_cost = 0;
	std::vector<Edge> mst_edges;

	for (auto& edge : edges) {
		if (!dsu.sameSet(edge.u, edge.v)) {
			dsu.unite(edge.u, edge.v);
			mst_cost += edge.w;
			mst_edges.push_back(edge);
		}
	}

	std::cout << "Min Cost ---> " << mst_cost << std::endl;
	for (const auto& edge : mst_edges)
		std::cout << edge.u << " --- " << edge.v << " : " << edge.w << std::endl;
}

int main() {
	int n = 5;
	std::vector<Edge> edges = {
		{0, 1, 1}, {0, 2, 3}, {1, 2, 3},
		{1, 3, 6}, {2, 3, 4}, {2, 4, 2}, {3, 4, 5}
	};
	kruskal_mst(n, edges);
	return 0;
}
