#ifndef ARC_GRAPH_H_
#define ARC_GRAPH_H_

#include "graph_interface.h"

using std::pair;

class ArcGraph : public IGraph {
public:
    ArcGraph(int count);
    ArcGraph(const IGraph& graph);

	virtual ~ArcGraph() = default;

	virtual void addEdge( int from, int to ) override;

	virtual int verticesCount() const override;

	virtual vector<int> getNextVertices( int vertex ) const override;
	virtual vector<int> getPrevVertices( int vertex ) const override;

private:
    vector<pair<int, int>> _arc_graph;
    int _count;

};

#endif  // ARC_GRAPH_H_
