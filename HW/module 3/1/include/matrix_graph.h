#ifndef MATRIX_GRAPH_H_
#define MATRIX_GRAPH_H_

#include "graph_interface.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(int count);
    MatrixGraph( const IGraph& graph );

	virtual ~MatrixGraph() = default;

	virtual void addEdge( int from, int to ) override;

	virtual int verticesCount() const override;

	virtual vector<int> getNextVertices( int vertex ) const override;
	virtual vector<int> getPrevVertices( int vertex ) const override;

private:
    vector<vector<int>> _matr_graph;

};

#endif  // MATRIX_GRAPH_H_