#include <iostream>
#include <vector>
#include <utility>
#include <queue>

static const long long INF = 1e15;

std::vector<long long> dijkstra(std::vector<std::vector<std::pair<int,int>>>& adj, int source) {
	int n = adj.size();
	std::vector<long long> dist(n, INF);
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
		std::greater<std::pair<int, int>>> pq;

	dist[source] = 0;
	pq.push({0, source});
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d > dist[u])
			continue;
		for (auto [v, w] : adj[u]) {
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
	}
	return dist;
}

void print_dist(const std::vector<long long>& dist) {
	for (size_t i = 0; i < dist.size(); ++i) {
		if (dist[i] == INF)
			std::cout << "INF ";
		else
			std::cout << dist[i] << " ";
	}
	std::cout << "\n";
}

int main() {

	// =========================
	// 🔹 Test 1: Simple graph
	// =========================
	{
		std::cout << "Test 1:\n";

		int n = 5;
		std::vector<std::vector<std::pair<int,int>>> adj(n);

		adj[0].push_back({1, 2});
		adj[0].push_back({2, 4});
		adj[1].push_back({2, 1});
		adj[1].push_back({3, 7});
		adj[2].push_back({4, 3});
		adj[3].push_back({4, 1});

		std::vector<long long> dist = dijkstra(adj, 0);
		print_dist(dist);
		// expected: 0 2 3 9 6
	}

	// =========================
	// 🔹 Test 2: Disconnected graph
	// =========================
	{
		std::cout << "Test 2:\n";

		int n = 6;
		std::vector<std::vector<std::pair<int,int>>> adj(n);

		adj[0].push_back({1, 5});
		adj[1].push_back({2, 2});
		adj[2].push_back({3, 1});
		// nodes 4 and 5 are disconnected

		std::vector<long long> dist = dijkstra(adj, 0);
		print_dist(dist);
		// expected: 0 5 7 8 INF INF
	}

	// =========================
	// 🔹 Test 3: Multiple paths
	// =========================
	{
		std::cout << "Test 3:\n";

		int n = 4;
		std::vector<std::vector<std::pair<int,int>>> adj(n);

		adj[0].push_back({1, 10});
		adj[0].push_back({2, 1});
		adj[2].push_back({1, 2});
		adj[1].push_back({3, 1});
		adj[2].push_back({3, 5});

		std::vector<long long> dist = dijkstra(adj, 0);
		print_dist(dist);
		// expected: 0 3 1 4
	}

	return 0;
}
