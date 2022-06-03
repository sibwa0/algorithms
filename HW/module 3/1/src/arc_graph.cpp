#include "arc_graph.h"

ArcGraph::ArcGraph(int count)
{
    _arc_graph.resize(count);
}

ArcGraph::ArcGraph(const IGraph& graph)
{
    _arc_graph.resize(graph.verticesCount());

    for (int i = 0; i < _arc_graph.size(); ++i) {
        vector<int> row = graph.getNextVertices(i);
        for (int j = 0; j < row.size(); ++j) {
            _arc_graph.emplace_back(i, row[j]);
        }
    }
}

void ArcGraph::addEdge( int from, int to )
{
    _arc_graph.emplace_back(from, to);
}

int ArcGraph::verticesCount() const
{
    return _arc_graph.size();
}

vector<int> ArcGraph::getNextVertices( int vertex ) const
{
    vector<int> nextVertices;

    for (int i = 0; i < _arc_graph.size(); ++i) {
        if (_arc_graph[i].first == vertex) {
            nextVertices.push_back(_arc_graph[i].second);
        }
    }

    return nextVertices;
}

vector<int> ArcGraph::getPrevVertices( int vertex ) const
{
    vector<int> prevVertices;

    for (int i = 0; i < _arc_graph.size(); ++i) {
        if (_arc_graph[i].second == vertex) {
            prevVertices.push_back(_arc_graph[i].first);
        }
    }

    return prevVertices;
}
