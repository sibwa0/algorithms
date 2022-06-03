#ifndef SET_GRAPH_H_
#define SET_GRAPH_H_

#include "graph_interface.h"

#include <set>

using std::set;

class SetGraph : public IGraph {
public:
    SetGraph(int count);
    SetGraph(const IGraph& graph);

	virtual ~SetGraph() = default;

	virtual void addEdge( int from, int to ) = 0;

	virtual int verticesCount() const = 0;

	virtual std::vector<int> getNextVertices( int vertex ) const = 0;
	virtual std::vector<int> getPrevVertices( int vertex ) const = 0;

private:
    vector<set<int>> _set_graph;

};

#endif  // SET_GRAPH_H_
