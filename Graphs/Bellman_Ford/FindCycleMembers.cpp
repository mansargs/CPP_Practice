#include <iostream>
#include <utility>
#include <vector>

using pii = std::pair<int, int>;
static const int INF = 1e8;

std::vector<int> bellman_ford(int src, std::vector<std::vector<pii>>& adj) {
	int n = adj.size();
	std::vector<int> dist(n, INF);
	std::vector<int> parent(n, -1);
	dist[src] = 0;
	int last_updated = -1;
	
	for (int i = 0; i < n; ++i) {
		last_updated = -1;
		for (int u = 0; u < n; ++u) {
			for (auto [v, w] : adj[u]) {
				if (dist[u] != INF && dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
					parent[v] = u;
					last_updated = v;
				}
			}
		}
	}
	if (last_updated == -1)
		return {};
	int cycle_vertex = last_updated;
	for (int i = 0; i < n; ++i)
		cycle_vertex = parent[cycle_vertex];
	std::vector<int> cycle;
	int v = cycle_vertex;
	do {
		cycle.push_back(v);
		v = parent[v];
	} while (v != cycle_vertex);
	return cycle;
}

int main() {
	// ===== Case 1: No negative cycle =====
	{
		std::cout << "=== Case 1: No Negative Cycle ===\n";
		int n = 5;
		std::vector<std::vector<pii>> adj(n);
		adj[0].push_back({1, 6});
		adj[0].push_back({2, 7});
		adj[1].push_back({3, 5});
		adj[1].push_back({4, -4});
		adj[2].push_back({3, -3});
		adj[3].push_back({1, -2});
		adj[4].push_back({3, 7});
		std::vector<int> cycle = bellman_ford(0, adj);
		if (cycle.empty()) {
			std::cout << "No negative cycle\n";
		} else {
			std::cout << "Vertices inside negative cycle: ";
			for (int v : cycle) std::cout << v << " ";
			std::cout << "\n";
		}
	}
	std::cout << "\n";

	// ===== Case 2: With negative cycle =====
	{
		std::cout << "=== Case 2: With Negative Cycle ===\n";
		int n = 4;
		std::vector<std::vector<pii>> adj(n);
		adj[0].push_back({1, 1});
		adj[1].push_back({2, -1});
		adj[2].push_back({3, -1});
		adj[3].push_back({1, -1}); // cycle: 1 → 2 → 3 → 1 (negative)
		std::vector<int> cycle = bellman_ford(0, adj);
		if (cycle.empty()) {
			std::cout << "No negative cycle\n";
		} else {
			std::cout << "Vertices inside negative cycle: ";
			for (int v : cycle) std::cout << v << " ";
			std::cout << "\n";
		}
	}
	return 0;
}
