#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <sstream>
#include <set>

using std::vector;
using std::queue;
using std::pair;
using std::set;

class WeightedGraph {
public:
    WeightedGraph(int count);
    ~WeightedGraph() = default;

    void addEdge(int from, int to, int weight);

    int verticesCount() const;

    vector<pair<int, int>> getNextVertices(int vertex) const;
    vector<pair<int, int>> getPrevVertices(int vertex) const;

private:
    vector<vector<pair<int, int>>> _weighted_graph;

};


WeightedGraph::WeightedGraph(int count)
{
    _weighted_graph.resize(count);
}

void WeightedGraph::addEdge(int from, int to, int weight)
{
    _weighted_graph[from].emplace_back(to, weight);
    _weighted_graph[to].emplace_back(from, weight);
}

int WeightedGraph::verticesCount() const
{
    return _weighted_graph.size();
}

vector<pair<int, int>> WeightedGraph::getNextVertices(int vertex) const
{
    return _weighted_graph[vertex];
}

class Cmp {
public:
    bool operator()(std::pair<int, int> a, std::pair<int, int> b) 
    {
        return (a.second == b.second) ? a.first < b.first : a.second < b.second;
    }
};

int getDeikstraPath(const WeightedGraph& graph, int from, int to)
{
    vector<int> parent(graph.verticesCount(), -1);
    vector<int> distance(graph.verticesCount(), 0);

    Cmp cmp;
    set<pair<int, int>, decltype(cmp)> s(cmp);
    s.emplace(from, 0);

    while (!s.empty()) {
        auto cur = s.begin()->first;
        s.erase(*s.begin());

        for (auto vertex : graph.getNextVertices(cur)) {
            if (vertex.first != cur || vertex.first == to) {
                if (distance[vertex.first] > distance[cur] + vertex.second) {
                    s.erase(pair<int, int>(vertex.first, distance[vertex.first]));

                    distance[vertex.first] = distance[cur] + vertex.second;
                    parent[vertex.first] = cur;

                    s.emplace(vertex.first, distance[vertex.first]);
                } else if (parent[vertex.first] == -1) {
                    parent[vertex.first] = cur;
                    distance[vertex.first] = distance[cur] + vertex.second;

                    s.emplace(vertex.first, distance[vertex.first]);
                
                }
            }
        }
    }

    return distance[to];

}


int run(std::istream& input, std::ostream& output) {
    int v;
	input >> v;

	WeightedGraph g(v);
	int n;
	input >> n;

    int from;
    int to;
    int weight;
	for (int i = 0; i < n; ++i) {
		input >> from >> to >> weight;
		g.addEdge(from, to, weight);
	}

    input >> from >> to;

	output << getDeikstraPath(g, from, to) << std::endl;

	return 0;
}

void testPath()
{
    {
		std::stringstream input;
		std::stringstream output;
		input << "6 9 0 3 1 0 4 2 1 2 7 1 3 2 1 4 3 1 5 3 2 5 3 3 4 4 3 5 6 0 2";
		run(input, output);
		assert(output.str() == "9\n");
	}
}

int main()
{
	testPath();
	// run(std::cin, std::cout);
	return 0;
}