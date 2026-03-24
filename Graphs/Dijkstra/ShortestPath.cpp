#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>

static const size_t INF = 1e8;

using pss = std::pair<size_t, size_t>;

std::vector<int> dijkstra(size_t start, size_t end, std::vector<std::vector<pss>> adj) {
	size_t n = adj.size();
	std::vector<size_t> dist(n, INF);
	std::vector<int> parent(n, -1);
	std::priority_queue<pss, std::vector<pss>, std::greater<pss>> pq;

	dist[start] = 0;
	pq.push({0, start});
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d > dist[u])
			continue ;
		for (auto [v, w] : adj[u]) {
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				parent[v] = u;
				pq.push({dist[v], v});
			}
		}
	}
	std::cout << "Shortest distance from " << start << " to " << end << " = " << dist[end] << "\n";
	return parent;
}

void reconstruct(std::vector<int>& parent, int end) {
	std::vector<int> path;
	for(int curr = end; curr != -1; curr = parent[curr]) {
		path.push_back(curr);
	}
	std::reverse(path.begin(), path.end());
	std::copy(path.begin(), path.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
}

// ---------------- Tester main ----------------
int main() {
	size_t n = 5;
	size_t start = 0;
	size_t end = 4;
	std::vector<std::vector<pss>> adj(n);


	adj[0].push_back({1, 2});
	adj[0].push_back({2, 4});
	adj[1].push_back({2, 1});
	adj[1].push_back({3, 7});
	adj[2].push_back({4, 3});
	adj[3].push_back({4, 1});

	std::vector<int> parent = dijkstra(start, end, adj);
	std::cout << "Shortest path: ";
	reconstruct(parent, end);

	return 0;
}
