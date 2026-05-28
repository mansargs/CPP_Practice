#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using tiii = std::tuple<int, int, int>;

int prims_mst(int n, const std::vector<std::vector<std::pair<int, int>>>& adj) {
	std::vector<int> parent(n, -1);
	std::vector<bool> used(n, false);
	std::priority_queue<tiii, std::vector<tiii>, std::greater<tiii>> pq;
	int total = 0;

	pq.push({0, 0, -1});
	while (!pq.empty()) {
		auto [w, u, p] = pq.top();
		pq.pop();
		if (used[u])
			continue;
		used[u] = true;
		total += w;
		parent[u] = p;
		for (auto &[v, wt] : adj[u]) {
			if (!used[v])
				pq.push({wt, v, u});
		}
	}
	std::cout << "MST edges\n";
	for (int i = 0; i < n; ++i) {
		if (parent[i] != -1)
			std::cout << parent[i] << "-" << i << std::endl;
	}
	return total;
}

int main() {
	int V = 3;
	std::vector<std::vector<std::pair<int,int>>> adj(V);

	adj[0].push_back({1, 5});
	adj[1].push_back({0, 5});

	adj[1].push_back({2, 3});
	adj[2].push_back({1, 3});

	adj[0].push_back({2, 1});
	adj[2].push_back({0, 1});

	int total = prims_mst(V, adj);
	std::cout << "Total weight of MST: " << total << "\n";
	return 0;
}

