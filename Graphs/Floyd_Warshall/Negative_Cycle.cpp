#include <iostream>
#include <vector>

const long long INF = 1e15;

void floyd_warshall(std::vector<std::vector<long long>>& mat) {
	int n = mat.size();
	for (int k= 0; k < n; ++k) {
		for (int i= 0; i < n; ++i) {
			for (int j= 0; j < n; ++j) {
				if (mat[i][j] > mat[i][k] + mat[k][j])
					mat[i][j] = mat[i][k] + mat[k][j];
			}
		}
	}
}

bool negative_cycle_detection(std::vector<std::vector<long long>>& mat) {
	floyd_warshall(mat);
	int n = mat.size();
	bool result = false;
	for (int k = 0; k < n; ++k) {
		if (mat[k][k] < 0) {
			result = true;
			for (int i = 0; i < n; ++i) {
				for (int j= 0; j < n; ++j) {
					if (mat[i][k] != INF && mat[k][j] != INF)
						mat[i][j] = -INF;
				}
			}
		}
	}
	return result;
}

struct TestCase {
		int n;
		std::vector<std::vector<long long>> edges;
		bool expectCycle;
};

int main() {
	std::vector<TestCase> tests = {
		// Test 1: negative cycle exists
		{3, {{0,1,1},{1,2,-3},{2,0,1}}, true},
		// Test 2: no negative cycle
		{3, {{0,1,2},{1,2,3},{2,0,1}}, false},
		// Test 3: self-loop negative cycle
		{2, {{0,0,-5}}, true},
		// Test 4: disconnected nodes, no cycle
		{3, {}, false}
	};
	for (int t = 0; t < tests.size(); ++t) {
		int n = tests[t].n;
		std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, INF));
		for (int i = 0; i < n; i++) dist[i][i] = 0;
		for (auto &e : tests[t].edges) {
			int u = e[0], v = e[1], w = e[2];
			dist[u][v] = w;
		}
		bool hasCycle = negative_cycle_detection(dist);
		if (hasCycle == tests[t].expectCycle)
			std::cout << "Test " << t+1 << ": ok\n";
		else
			std::cout << "Test " << t+1 << ": ko\n";
	}
	return 0;
}
