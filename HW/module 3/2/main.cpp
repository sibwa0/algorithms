#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <sstream>

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

ListGraph::ListGraph( int count )
{
	_adj_list.resize( count );
}

ListGraph::ListGraph( const IGraph& graph )
{
	_adj_list.resize( graph.verticesCount() );
	for( int i = 0; i < graph.verticesCount(); ++i ) {
		_adj_list[i] = graph.getNextVertices( i );
	}
}

void ListGraph::addEdge( int from, int to )
{
	assert( from >= 0 && from < _adj_list.size() );
	assert( to >= 0 && to < _adj_list.size() );
	_adj_list[from].push_back( to );
}

int ListGraph::verticesCount() const
{
	return _adj_list.size();
}

std::vector<int> ListGraph::getNextVertices( int vertex ) const
{
	assert( vertex >= 0 && vertex < _adj_list.size() );
	return _adj_list[vertex];
}

std::vector<int> ListGraph::getPrevVertices( int vertex ) const
{
	assert( vertex >= 0 && vertex < _adj_list.size() );
	vector<int> prevVerticies;
	for( int from = 0; from < _adj_list.size(); ++from )
		for( int i = 0; i < _adj_list[from].size(); ++i )
			if( _adj_list[from][i] == vertex )
				prevVerticies.push_back( from );
	return prevVerticies;
}


int getNumShortestPaths(const IGraph& graph, const int& from, const int& to) {
    vector<int> cnt(graph.verticesCount(), 0);

    vector<int> cnt_btw_points(graph.verticesCount(), INT16_MAX);
    cnt[from] = 1;
	cnt_btw_points[from] = 0;

    queue<int> q;
    q.push(from);


    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

		for (auto child : graph.getNextVertices(vertex)) {
			if (cnt_btw_points[child] > cnt_btw_points[vertex] + 1) {
				cnt_btw_points[child] = cnt_btw_points[vertex] + 1;
				cnt[child] = cnt[vertex];
				q.push(child);
			} else if (cnt_btw_points[child] == cnt_btw_points[vertex] + 1) {
				cnt[child] += cnt[vertex];
			}
		}
    }

    return cnt[to];
}


int run(std::istream& input, std::ostream& output) {
    int v;
	input >> v;

	IGraph* g = new ListGraph(v);
	int n;
	input >> n;

    int from;
    int to;
	for (int i = 0; i < n; ++i) {
		input >> from >> to;
		g->addEdge(from, to);
		g->addEdge(to, from);
	}

    input >> from >> to;

	output << getNumShortestPaths(*g, from, to) << std::endl;

	return 0;
}

void testShortestPaths()
{
    {
		std::stringstream input;
		std::stringstream output;
		input << "4 5 0 1 0 2 1 2 1 3 2 3 0 3";
		run(input, std::cout);
		// assert(output.str() == "2\n");
	}
}

int main()
{
	// testShortestPaths();
	run(std::cin, std::cout);
	return 0;
}
