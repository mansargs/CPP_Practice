#include <iostream>
#include <vector>
#include <stdexcept>

class AdjMatrix {
	private:
		std::vector<std::vector<size_t>> adj;

		void addNeighbor(size_t v, size_t neighbor) {
			if (v >= adj.size() || neighbor >= adj.size()) {
				throw std::out_of_range("Vertex index out of range");
			}
			adj[v][neighbor] = 1;
		}
	public:
		explicit AdjMatrix(size_t n) {
			adj.resize(n);
			for (auto& row : adj)
				row.resize(n, 0);
		}
		~AdjMatrix() = default;

		void addEdge(size_t u, size_t v, bool undirected = false) {
			addNeighbor(u, v);
			if (undirected)
				addNeighbor(v, u);
		}

		void print() const {
			for (size_t i = 0; i < adj.size(); ++i) {
				for (size_t field : adj[i]) {
					std::cout << field << " ";
				}
				std::cout << "\n";
			}
		}

		size_t size() const {
			return adj.size();
		}

		const std::vector<size_t>& neighbors(size_t v) const {
			if (v >= adj.size()) {
				throw std::out_of_range("Vertex index out of range");
			}
			return adj[v];
		}
};

int main() {
	AdjMatrix graph(4);

	graph.addEdge(0, 1, true);
	graph.addEdge(0, 2, true);
	graph.addEdge(1, 3, true);
	graph.addEdge(2, 3, true);

	std::cout << "Adjacency Matrix:\n";
	graph.print();

	return 0;
}
