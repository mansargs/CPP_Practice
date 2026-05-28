#include <iostream>
#include <vector>

const long long INF = 1e15;

std::vector<std::vector<int>> floay_warshall(std::vector<std::vector<long long>>& mat) {
	int n = mat.size();
	std::vector<std::vector<int>> path(n, std::vector<int>(n, -1));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (mat[i][j] != INF)
				path[i][j] = j;
		}
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (mat[i][j] > mat[i][k] + mat[k][j]) {
					mat[i][j] = mat[i][k] + mat[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
	return path;
}

std::vector<int> recover_path(int u, int v, std::vector<std::vector<int>>& path) {
	std::vector<int> p = {u};
	while (u != v) {
		u = path[u][v];
		p.push_back(u);
	}
	return p;
}

void print_vector(const std::vector<int>& v) {
	if (v.empty()) {
		std::cout << "No path\n";
		return ;
	}
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i];
		if (i != v.size() - 1)
			std::cout << "->";
	}
	std::cout << std::endl;
}

int main() {
	int n = 3;
	std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, INF));
	for (int i = 0; i < n; i++) dist[i][i] = 0;
	dist[0][1] = 2;
	dist[0][2] = 10;
	dist[1][2] = 3;

	std::vector<std::vector<int>> next = floay_warshall(dist);

	std::cout << "Path 0 -> 2: ";
	std::vector<int> p0_2 = recover_path(0, 2, next);
	print_vector(p0_2);

	std::cout << "Path 0 -> 1: ";
	std::vector<int> p0_1 = recover_path(0, 1, next);
	print_vector(p0_1);

	std::cout << "Path 1 -> 2: ";
	std::vector<int> p1_2 = recover_path(1, 2, next);
	print_vector(p1_2);

	std::cout << "\nDistance matrix:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dist[i][j] == INF) std::cout << "INF ";
			else std::cout << dist[i][j] << " ";
		}
		std::cout << "\n";
	}

	return 0;
}
