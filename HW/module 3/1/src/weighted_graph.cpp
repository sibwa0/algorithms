#include "weighted_graph.h"

#include "weighted_graph.h"

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