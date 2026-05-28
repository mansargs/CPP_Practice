#include <iostream>
#include <vector>
#include <stack>

void dfsTopo(int node, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::stack<int>& st) {
	visited[node] = true;
	for (int neighbor : adj[node]) {
		if (!visited[neighbor])
			dfsTopo(neighbor, adj, visited, st);
	}
	st.push(node);
}

std::vector<int> topoSortGlobal(const std::vector<std::vector<int>>& adj) {
	size_t n = adj.size();
	std::vector<bool> visited(n, false);
	std::stack<int> st;

	for (size_t i = 0; i < n; ++i) {
		if (!visited[i])
			dfsTopo(i, adj, visited, st);
	}
	std::vector<int> order;
	while (!st.empty()) {
		order.push_back(st.top());
		st.pop();
	}
	return order;
}

void printVector(const std::vector<int>& v) {
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
		int n = 6;
		std::vector<std::vector<int>> adj(n);
		adj[5] = {2, 0};
		adj[4] = {0, 1};
		adj[2] = {3};
		adj[3] = {1};

		std::cout << "Test 1 Global Topo Order: ";
		printVector(topoSortGlobal(adj));
		// Example expected: 4->5->2->3->1->0
	}

	// ---------- Test 2: Disconnected components ----------
	{
		int n = 5;
		std::vector<std::vector<int>> adj(n);
		adj[0] = {1};
		adj[2] = {3};

		std::cout << "Test 2 Global Topo Order: ";
		printVector(topoSortGlobal(adj));
		// Example expected: 2->3->0->1->4 (or similar)
	}

	// ---------- Test 3: Single node ----------
	{
		int n = 1;
		std::vector<std::vector<int>> adj(n);

		std::cout << "Test 3 Global Topo Order: ";
		printVector(topoSortGlobal(adj));
		// Expected: 0
	}

	// ---------- Test 4: Linear chain ----------
	{
		int n = 4;
		std::vector<std::vector<int>> adj(n);
		adj[0] = {1};
		adj[1] = {2};
		adj[2] = {3};

		std::cout << "Test 4 Global Topo Order: ";
		printVector(topoSortGlobal(adj));
		// Expected: 0->1->2->3
	}

	// ---------- Test 5: Multiple nodes with no edges ----------
	{
		int n = 3;
		std::vector<std::vector<int>> adj(n);

		std::cout << "Test 5 Global Topo Order: ";
		printVector(topoSortGlobal(adj));
		// Any order valid: 0->1->2 (or 2->1->0 etc.)
	}

	return 0;
}
