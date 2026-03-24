#include <iostream>
#include <vector>
#include <queue>

static const long long INF = 1e15;

using pll = std::pair<long long, long long>;

std::vector<long long> multi_source_dijkstra(const std::vector<long>& sources, std::vector<std::vector<pll>>& adj) {
	long n = adj.size();
	std::vector<long long> dist(n, INF);
	std::priority_queue<pll, std::vector<pll>, std::greater<pll>> pq;

	for (size_t i = 0; i < sources.size(); ++i) {
		dist[sources[i]] = 0;
		pq.push({0, sources[i]});
	}
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d > dist[u])
			continue ;
		for (auto [v, w] : adj[u]) {
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
	}
	return dist;
}

int main() {
	long n = 6;
	std::vector<std::vector<pll>> adj(n);

	adj[0].push_back({2, 1});
	adj[0].push_back({5, 2});
	adj[1].push_back({2, 2});
	adj[1].push_back({1, 3});
	adj[2].push_back({3, 4});
	adj[3].push_back({1, 4});
	adj[4].push_back({2, 5});

	// Multi sources
	std::vector<long> sources = {0, 2};
	std::vector<long long> dist = multi_source_dijkstra(sources, adj);
	std::cout << "Shortest distances from sources {0, 2}:\n";
	for (long i = 0; i < n; ++i) {
		if (dist[i] == INF)
			std::cout << i << ": INF\n";
		else
			std::cout << i << ": " << dist[i] << "\n";
	}
	return 0;
}
