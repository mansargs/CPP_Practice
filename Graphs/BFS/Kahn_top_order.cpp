#include <iostream>
#include <vector>
#include <queue>

std::vector<size_t> Kahn_top_order(std::vector<std::vector<int>>& adj) {
	size_t n = adj.size();
	std::vector<size_t> indegre(n, 0);
	std::queue<ssize_t> q;
	std::vector<size_t> order;

	for (size_t i = 0; i < n; ++i)
		for (int next : adj[i])
			indegre[next]++;
	for (size_t i = 0; i < n; ++i) {
		if (indegre[i] == 0)
			q.push(i);
	}
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		order.push_back(node);
		for (auto neighbor : adj[node]) {
			--indegre[neighbor];
			if (indegre[neighbor] == 0)
				q.push(neighbor);
		}
	}
	if (order.size() != n) {
		std::cout << "Graph has a cycle! Topological sort not possible.\n";
		return {};
	}
	return order;
}

void printVector(const std::vector<size_t>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		 std::cout << v[i];
		 if (i + 1 != v.size())
		 	std::cout << "->";
	}
	std::cout << std::endl;
}

int main() {
	// ---------- Test 1: Simple DAG ----------
	{
		std::cout << "--- Test 1: Simple DAG ---\n";
		int n = 6;
		std::vector<std::vector<int>> adj(n);
		adj[5] = {2, 0};
		adj[4] = {0, 1};
		adj[2] = {3};
		adj[3] = {1};

		std::vector<size_t> order = Kahn_top_order(adj);
		std::cout << "Kahn Topo Order: ";
		printVector(order);
		// Expected: a valid topo order, e.g., 4->5->2->3->1->0
	}

	// ---------- Test 2: Disconnected components ----------
	{
		std::cout << "\n--- Test 2: Disconnected components ---\n";
		int n = 5;
		std::vector<std::vector<int>> adj(n);
		adj[0] = {1};
		adj[2] = {3};

		std::vector<size_t> order = Kahn_top_order(adj);
		std::cout << "Kahn Topo Order: ";
		printVector(order);
		// Example valid: 0->2->1->3->4 or any order respecting edges
	}

	// ---------- Test 3: Single node ----------
	{
		std::cout << "\n--- Test 3: Single node ---\n";
		int n = 1;
		std::vector<std::vector<int>> adj(n);

		std::vector<size_t> order = Kahn_top_order(adj);
		std::cout << "Kahn Topo Order: ";
		printVector(order);
		// Expected: 0
	}

	// ---------- Test 4: Linear chain ----------
	{
		std::cout << "\n--- Test 4: Linear chain ---\n";
		int n = 4;
		std::vector<std::vector<int>> adj(n);
		adj[0] = {1};
		adj[1] = {2};
		adj[2] = {3};

		std::vector<size_t> order = Kahn_top_order(adj);
		std::cout << "Kahn Topo Order: ";
		printVector(order);
		// Expected: 0->1->2->3
	}

	// ---------- Test 5: Multiple nodes with no edges ----------
	{
		std::cout << "\n--- Test 5: Nodes with no edges ---\n";
		int n = 3;
		std::vector<std::vector<int>> adj(n);

		std::vector<size_t> order = Kahn_top_order(adj);
		std::cout << "Kahn Topo Order: ";
		printVector(order);
		// Any order valid: 0->1->2 (or 2->1->0 etc.)
	}

	// ---------- Test 6: Cycle detection ----------
	{
		std::cout << "\n--- Test 6: Graph with a cycle ---\n";
		int n = 3;
		std::vector<std::vector<int>> adj(n);
		adj[0] = {1};
		adj[1] = {2};
		adj[2] = {0}; // cycle 0->1->2->0

		std::vector<size_t> order = Kahn_top_order(adj);
		// Output: Graph has a cycle! Topological sort not possible.
	}

	return 0;
}
