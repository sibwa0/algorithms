#ifndef LIST_GRAPH_H_
#define LIST_GRAPH_H_

#include "graph_interface.h"

// list graph
class ListGraph : public IGraph {
public:
	ListGraph( int count );
	ListGraph( const IGraph& graph );

	virtual ~ListGraph() = default;

	virtual void addEdge( int from, int to ) override;

	virtual int verticesCount() const override;

	virtual std::vector<int> getNextVertices( int vertex ) const override;
	virtual std::vector<int> getPrevVertices( int vertex ) const override;

private:
	vector<vector<int>> _adj_list;

};

#endif  // LIST_GRAPH_H_