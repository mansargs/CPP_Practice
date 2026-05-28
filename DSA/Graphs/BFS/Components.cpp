#include <iostream>
#include <vector>
#include <queue>

void bfs(int v, const std::vector<std::vector<int>> &adjList, std::vector<bool> &visited) {
	std::queue<int> q;

	q.push(v);
	visited[v] = true;

	while (!q.empty()) {
		int node = q.front();
		q.pop();
		for (const auto& neighbor : adjList[node]) {
			if (!visited[neighbor]) {
				q.push(neighbor);
				visited[neighbor] = true;
			}
		}
	}
}

size_t componentsCount(const std::vector<std::vector<int>> &adjList) {
	size_t n = adjList.size();
	std::vector<bool> visited(n, false);
	size_t count = 0;

	for (size_t i = 0; i < n; ++i) {
		if (!visited[i]) {
			++count;
			bfs(i, adjList, visited);
		}
	}
	return count;
}

int main() {
	std::vector<std::vector<int>> adjList(6);

	adjList[0].push_back(1);
	adjList[1].push_back(0);

	adjList[1].push_back(2);
	adjList[2].push_back(1);

	adjList[3].push_back(4);
	adjList[4].push_back(3);

	std::cout << "Number of connected components: " << componentsCount(adjList) << std::endl;
	return 0;
}
