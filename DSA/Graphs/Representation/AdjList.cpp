#include <iostream>
#include <vector>
#include <stdexcept>

class AdjList {
	private:
		std::vector<std::vector<size_t>> adj;

		void addNeighbor(size_t v, size_t neighbor) {
			if (v >= adj.size() || neighbor >= adj.size()) {
				throw std::out_of_range("Vertex index out of range");
			}
			adj[v].push_back(neighbor);
		}
	public:
		explicit AdjList(size_t n) {
			adj.resize(n);
		}
		~AdjList() = default;

		void addEdge(size_t u, size_t v, bool undirected = false) {
			addNeighbor(u, v);
			if (undirected)
				addNeighbor(v, u);
		}

		void print() const {
			for (size_t i = 0; i < adj.size(); ++i) {
				std::cout << i << ": ";
				for (size_t neighbor : adj[i]) {
					std::cout << neighbor << " ";
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
	AdjList graph(6);

	graph.addEdge(0, 1, true);
	graph.addEdge(0, 2, true);
	graph.addEdge(1, 3, true);
	graph.addEdge(4, 5, true);

	std::cout << "Adjacency List:\n";
	graph.print();

	return 0;
}
