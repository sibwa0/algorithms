#include "matrix_graph.h"

MatrixGraph::MatrixGraph(int count)
{
    _matr_graph.resize(count);
}

MatrixGraph::MatrixGraph( const IGraph& graph )
{
    _matr_graph.resize(graph.verticesCount());

    for (int i = 0; i < graph.verticesCount(); ++i) {
        vector<int> row = graph.getNextVertices(i);
        for (int j = 0; j < row.size(); ++j) {
            _matr_graph[i][row[j]] = 1;
        }
    }
}

void MatrixGraph::addEdge( int from, int to )
{
    _matr_graph[from][to] = 1;
}

int MatrixGraph::verticesCount() const
{
    _matr_graph.size();
}

vector<int> MatrixGraph::getNextVertices( int vertex ) const
{
    vector<int> nextVertices;

    for (int i = 0; i < _matr_graph.size(); ++i) {
        if (_matr_graph[vertex][i] == 1) {
            nextVertices.push_back(i);
        }
    }

    return nextVertices;
}

vector<int> MatrixGraph::getPrevVertices( int vertex ) const
{
    vector<int> prevVertices;

    for (int i = 0; i < _matr_graph.size(); ++i) {
        if (_matr_graph[i][vertex] == 1) {
            prevVertices.push_back(i);
        }
    }

    return prevVertices;
}