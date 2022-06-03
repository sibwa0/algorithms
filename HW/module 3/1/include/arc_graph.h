#ifndef ARC_GRAPH_H_
#define ARC_GRAPH_H_

#include "graph_interface.h"

using std::pair;

class ArcGraph : public IGraph {
public:
    ArcGraph(int count);
	virtual ~ArcGraph() = default;
    ArcGraph(const IGraph& graph);

	virtual void addEdge( int from, int to ) = 0;

	virtual int verticesCount() const = 0;

	virtual vector<int> getNextVertices( int vertex ) const = 0;
	virtual vector<int> getPrevVertices( int vertex ) const = 0;

private:
    vector<pair<int, int>> _arc_graph;
    int _count;

};

#endif  // ARC_GRAPH_H_
