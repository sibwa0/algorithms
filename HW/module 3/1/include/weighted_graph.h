#ifndef WEIGHTED_GRAPH_H_
#define WEIGHTED_GRAPH_H_

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

#endif  // WEIGHTED_GRAPH_H_