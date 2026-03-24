#include <iostream>
#include <vector>
#include <utility>

using pii = std::pair<int, int>;
static const  int INF = 1e8;

std::vector<int> bellman_ford(int src, std::vector<std::vector<pii>>& adj) {
	int n = adj.size();
	std::vector<int> dist(n, INF);
	std::vector<int> parent(n, -1);
	dist[src] = 0;

	int lastUpdated = -1;
	for (int i = 0; i < n; ++i) {
		lastUpdated = -1;
		for (int u = 0; u < n; ++u) {
			for (auto [v, w] : adj[u]) {
				if (dist[u] != INF && dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
					parent[v] = u;
					lastUpdated = v;
				}
			}
		}
	}
	if (lastUpdated != -1) {
		std::cout << "Has negative cycle\n";
	}
	return dist;
}

void print_distances(const std::vector<int>& v) {
	for (size_t i = 0; i < v.size(); ++i)
		std:: cout << i << ": " << v[i] << std::endl;
}

int main() {
	{
		std::cout << "=== Case 1: No Negative Cycle ===\n";
		int n = 5;
		std::vector<std::vector<std::pair<int,int>>> adj(n);
		adj[0].push_back({1, 6});
		adj[0].push_back({2, 7});
		adj[1].push_back({3, 5});
		adj[1].push_back({4, -4});
		adj[2].push_back({3, -3});
		adj[3].push_back({1, -2});
		adj[4].push_back({3, 7});
		auto dist = bellman_ford(0, adj);
		print_distances(dist);
	}
	std::cout << "\n";
	{
		std::cout << "=== Case 2: With Negative Cycle ===\n";
		int n = 4;
		std::vector<std::vector<std::pair<int,int>>> adj(n);
		adj[0].push_back({1, 1});
		adj[1].push_back({2, -1});
		adj[2].push_back({3, -1});
		adj[3].push_back({1, -1}); // cycle: 1 → 2 → 3 → 1 (negative)
		auto dist = bellman_ford(0, adj);
		print_distances(dist);
	}

	return 0;
}
