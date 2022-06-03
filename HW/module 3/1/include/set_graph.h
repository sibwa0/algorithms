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

	virtual void addEdge( int from, int to ) override;

	virtual int verticesCount() const override;

	virtual std::vector<int> getNextVertices( int vertex ) const override;
	virtual std::vector<int> getPrevVertices( int vertex ) const override;

private:
    vector<set<int>> _set_graph;

};

#endif  // SET_GRAPH_H_
