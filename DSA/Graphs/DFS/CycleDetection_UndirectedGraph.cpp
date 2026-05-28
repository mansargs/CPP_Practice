#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>

bool dfs(int start, int parent, std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
	std::stack<std::pair<int, int>> st;
	st.push({start, parent});
	while (!st.empty()) {
		auto [v, p] = st.top();
		st.pop();
		if (!visited[v])
			visited[v] = true;
		for (int neighbor : adj[v]) {
			if (!visited[neighbor]) {
				st.push({neighbor, v});
			}
			else if (neighbor != p)
				return true;
		}
	}
	return false;
}

std::size_t has_cycle(std::vector<std::vector<int>>& adj) {
	size_t n = adj.size();
	std::vector<bool> visited(n, false);

	for (size_t i = 0; i < n; i++)
	{
		if (!visited[i]) {
			if (dfs(i, -1, adj, visited))
				return true;
		}
	}
	return false;
}

int main() {

	// Test 1: No cycle (simple chain)
	{
		int n = 5;
		std::vector<std::vector<int> > adj(n);

		adj[0].push_back(1); adj[1].push_back(0);
		adj[1].push_back(2); adj[2].push_back(1);
		adj[2].push_back(3); adj[3].push_back(2);
		adj[3].push_back(4); adj[4].push_back(3);

		std::cout << has_cycle(adj) << "  // Expected: 0 (no cycle)" << std::endl;
	}

	// Test 2: Simple cycle
	{
		int n = 3;
		std::vector<std::vector<int> > adj(n);

		adj[0].push_back(1); adj[1].push_back(0);
		adj[1].push_back(2); adj[2].push_back(1);
		adj[2].push_back(0); adj[0].push_back(2);

		std::cout << has_cycle(adj) << "  // Expected: 1 (cycle)" << std::endl;
	}

	// Test 3: Disconnected graph with one cycle
	{
		int n = 6;
		std::vector<std::vector<int> > adj(n);

		adj[0].push_back(1); adj[1].push_back(0);

		adj[2].push_back(3); adj[3].push_back(2);
		adj[3].push_back(4); adj[4].push_back(3);
		adj[4].push_back(2); adj[2].push_back(4);

		std::cout << has_cycle(adj) << "  // Expected: 1 (cycle in one component)" << std::endl;
	}

	// Test 4: Fully connected graph
	{
		int n = 5;
		std::vector<std::vector<int> > adj(n);

		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}

		std::cout << has_cycle(adj) << "  // Expected: 1 (cycle exists)" << std::endl;
	}

	// Test 5: Single node
	{
		int n = 1;
		std::vector<std::vector<int> > adj(n);

		std::cout << has_cycle(adj) << "  // Expected: 0 (no cycle)" << std::endl;
	}

	// Test 6: Two nodes, one edge
	{
		int n = 2;
		std::vector<std::vector<int> > adj(n);

		adj[0].push_back(1);
		adj[1].push_back(0);

		std::cout << has_cycle(adj) << "  // Expected: 0 (no cycle)" << std::endl;
	}

	// Test 7: Self loop
	{
		int n = 3;
		std::vector<std::vector<int> > adj(n);

		adj[1].push_back(1);

		std::cout << has_cycle(adj) << "  // Expected: 1 (self-loop counts as cycle)" << std::endl;
	}

	// Test 8: Large chain (no cycle)
	{
		int n = 10000;
		std::vector<std::vector<int> > adj(n);

		for (int i = 0; i < n - 1; ++i) {
			adj[i].push_back(i + 1);
			adj[i + 1].push_back(i);
		}

		std::cout << has_cycle(adj) << "  // Expected: 0 (no cycle)" << std::endl;
	}

	// Test 9: Large cycle
	{
		int n = 10000;
		std::vector<std::vector<int> > adj(n);

		for (int i = 0; i < n - 1; ++i) {
			adj[i].push_back(i + 1);
			adj[i + 1].push_back(i);
		}

		adj[n - 1].push_back(0);
		adj[0].push_back(n - 1);

		std::cout << has_cycle(adj) << "  // Expected: 1 (cycle)" << std::endl;
	}

	// Test 10: Random graph
	{
		int n = 20;
		std::vector<std::vector<int> > adj(n);

		std::srand(std::time(0));
		for (int i = 0; i < 40; ++i) {
			int u = std::rand() % n;
			int v = std::rand() % n;
			if (u != v) {
				adj[u].push_back(v);
				adj[v].push_back(u);
			}
		}

		std::cout << has_cycle(adj) << "  // Expected: unpredictable (0 or 1)" << std::endl;
	}

	return 0;
}
