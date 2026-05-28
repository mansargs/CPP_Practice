#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>

using tiii = std::tuple<int, int, int>;

void prims_mst(size_t n, std::vector<std::vector<std::pair<int, int>>>& adj) {
	std::vector<bool> used(n, false);
	std::priority_queue<tiii, std::vector<tiii>, std::greater<tiii>> pq;

	for (size_t i = 0; i < n; ++i) {
		std::vector<int> parent(n, -1);
		int total = 0;
		if (used[i])
			continue ;
		pq.push({0, i, -1});
		while (!pq.empty()) {
			auto [w, u, p] = pq.top();
			pq.pop();
			if (used[u])
				continue;
			used[u] = true;
			parent[u] = p;
			total += w;
			for (auto [v, wt] : adj[u]) {
				if (!used[v])
					pq.push({wt, v, u});
			}
		}
		std::cout << "\nMST\n";
		for (int i = 0; i < n; ++i) {
			if (parent[i] != -1)
				std::cout << parent[i] << "-" << i << std::endl;
		}
		std::cout << "\nMin cost --> " << total << std::endl;
	}
}


int main() {
	using namespace std;
	// ===== Case 1: Disconnected graph =====
	{
		cout << "=== Case 1: Disconnected Graph ===\n";

		size_t n = 6; // 6 vertices: 0..5
		vector<vector<pair<int,int>>> adj(n);

		// Component 1
		adj[0].push_back({1, 4});
		adj[1].push_back({0, 4});

		adj[0].push_back({2, 3});
		adj[2].push_back({0, 3});

		adj[1].push_back({2, 2});
		adj[2].push_back({1, 2});

		// Component 2
		adj[3].push_back({4, 1});
		adj[4].push_back({3, 1});

		adj[4].push_back({5, 5});
		adj[5].push_back({4, 5});

		prims_mst(n, adj);
	}

	cout << "\n";

	// ===== Case 2: Single isolated vertex =====
	{
		cout << "=== Case 2: Isolated Vertex ===\n";

		size_t n = 3; // vertices 0,1,2
		vector<vector<pair<int,int>>> adj(n);

		// Only one edge
		adj[0].push_back({1, 7});
		adj[1].push_back({0, 7});

		// vertex 2 is isolated
		prims_mst(n, adj);
	}

	return 0;
}
