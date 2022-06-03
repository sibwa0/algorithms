#ifndef GRAPH_INTERFACE_H_
#define GRAPH_INTERFACE_H_

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

using std::vector;
using std::queue;

class IGraph {
public:
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void addEdge( int from, int to ) = 0;

	virtual int verticesCount() const = 0;

	virtual std::vector<int> getNextVertices( int vertex ) const = 0;
	virtual std::vector<int> getPrevVertices( int vertex ) const = 0;
};

#endif  // GRAPH_INTERFACE_H_
