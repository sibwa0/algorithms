#include "set_graph.h"

SetGraph::SetGraph(int count)
{
    _set_graph.resize(count);
}

SetGraph::SetGraph(const IGraph& graph)
{
    _set_graph.resize(graph.verticesCount());

    for (int i = 0; i < _set_graph.size(); ++i) {
        vector<int> row = graph.getNextVertices(i);

        for (int j = 0; j < row.size(); ++j) {
            _set_graph[i].insert(row[j]);
        }
    }
}

void SetGraph::addEdge( int from, int to )
{
    _set_graph[from].insert(to);
}

int SetGraph::SetGraph::verticesCount() const
{
    return _set_graph.size();
}

vector<int> SetGraph::getNextVertices( int vertex ) const
{
    vector<int> nextVertices;

    for (int i = 0; i < _set_graph.size(); ++i) {
        if (_set_graph[vertex].find(i) != _set_graph[vertex].end()) {
            nextVertices.push_back(i);
        }
    }

    return nextVertices;
}

vector<int> SetGraph::getPrevVertices( int vertex ) const
{
    vector<int> prevVertices;

    for (int i = 0; i < _set_graph.size(); ++i) {
        if (_set_graph[i].find(vertex) != _set_graph[i].end()) {
            prevVertices.push_back(i);
        }
    }

    return prevVertices;
}
