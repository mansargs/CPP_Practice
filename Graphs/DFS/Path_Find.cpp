#include <iostream>
#include <vector>
#include <stack>

void find_path(int curr, int end, std::vector<std::vector<int>>& adj, std::vector<int>& path, std::vector<std::vector<int>>& paths) {
	path.push_back(curr);
	if (curr == end)
		paths.push_back(path);
	else {
		for (int next : adj[curr])
			find_path(next, end, adj, path, paths);
	}
	path.pop_back();
}

void printVector(const std::vector<int>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i];
		if (i + 1 != v.size())
			std::cout << "->";
	}
	std::cout << std::endl;
}

void find_all_paths(int start, int end, std::vector<std::vector<int>>& adj) {
	std::vector<std::vector<int>> paths;
	std::vector<int> path;
	find_path(start, end, adj, path, paths);
	if (paths.empty()) {
		std::cout << "No path\n";
		return ;
	}
	std::cout << "All paths from " << start << " to " << end << ":\n";
	for (const auto& path : paths)
		printVector(path);
}

int main() {
	int n = 4;
	std::vector<std::vector<int>> adj(n);
	adj[0] = {1, 2};
	adj[1] = {3};
	adj[2] = {3};
	int start = 0, end = 3;
	find_all_paths(start, end, adj);
	return 0;
}

