#include <iostream>
#include <memory>
#include <vector>

class Vertex;

class Edge {
	public:
		std::shared_ptr<Vertex> from;
		std::shared_ptr<Vertex> to;
		int weight;

		Edge(std::shared_ptr<Vertex> f, std::shared_ptr<Vertex> t, int w = 1)
			: from(f), to(t), weight(w) {}
};

class Vertex {
	private:
		int id;
		std::vector<std::shared_ptr<Edge>> edges;
	public:
		explicit Vertex(int id) : id(id) {}
		~Vertex() = default;

	int getId() const { return id; }

	std::vector<std::shared_ptr<Edge>>& getEdges() {
		return edges;
	}
};

class Graph {
	private:
		std::vector<std::shared_ptr<Vertex>>  vertices;
	public:
		Graph() = default;

		std::shared_ptr<Vertex> addVertex(int id) {
			auto v = std::make_shared<Vertex>(id);
			vertices.push_back(v);
			return v;
		}

		 void addEdge(std::shared_ptr<Vertex> u, std::shared_ptr<Vertex> v, bool undirected = false, int weight = 1) {
		auto e1 = std::make_shared<Edge>(u, v, weight);
		u->getEdges().push_back(e1);
		if (undirected) {
			auto e2 = std::make_shared<Edge>(v, u, weight);
			v->getEdges().push_back(e2);
		}
	}

		void printGraph() const {
			for (const auto& v : vertices) {
				std::cout << v->getId() << ": ";
				for (const auto& e : v->getEdges()) {
					std::cout << e->to->getId() << "(" << e->weight << ") ";
				}
				std::cout << "\n";
			}
		}
};

int main () {
	Graph g;

	auto v0 = g.addVertex(0);
	auto v1 = g.addVertex(1);
	auto v2 = g.addVertex(2);
	auto v3 = g.addVertex(3);
	auto v4 = g.addVertex(4);
	auto v5 = g.addVertex(5);

	g.addEdge(v0, v1, true);
	g.addEdge(v0, v2, true);
	g.addEdge(v1, v3, true);
	g.addEdge(v4, v5, true);

	std::cout << "Graph representation:\n";
	g.printGraph();

	return 0;
}
