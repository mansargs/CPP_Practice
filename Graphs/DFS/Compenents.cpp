#include <iostream>
#include <vector>
#include <stack>

void dfs(int start, std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
	std::stack<int> st;

	st.push(start);
	visited[start] = true;
	while (!st.empty()) {
		int node = st.top();
		st.pop();

		for (int neighbor : adj[node]) {
			if (!visited[neighbor]) {
				st.push(neighbor);
				visited[neighbor] = true;
			}
		}
	}
}

std::size_t components_count(std::vector<std::vector<int>>& adj) {
	size_t count = 0;
	size_t n = adj.size();
	std::vector<bool> visited(n, false);

	for (size_t i = 0; i < n; i++)
	{
		if (!visited[i]) {
			dfs(i, adj, visited);
			++count;
		}
	}
	return count;
}


int main() {
	int n = 10;
	std::vector<std::vector<int> > adj(n);

	adj[0].push_back(1); adj[1].push_back(0);
	adj[1].push_back(2); adj[2].push_back(1);
	adj[2].push_back(3); adj[3].push_back(2);

	adj[4].push_back(5); adj[5].push_back(4);


	adj[7].push_back(8); adj[8].push_back(7);
	adj[8].push_back(9); adj[9].push_back(8);
	adj[9].push_back(7); adj[7].push_back(9);

	std::cout << "Components count is ->  " << components_count(adj) << std::endl;
}
