#include "arc_graph.h"
#include "list_graph.h"
#include "matrix_graph.h"
#include "set_graph.h"

#include <sstream>
#include <functional>

void BFS( const IGraph& graph, int vertex, std::function<void(int)> visit)
{
	vector<bool> visited( graph.verticesCount(), false );
	queue<int> bfsQueue;
	bfsQueue.push( vertex );
	visited[vertex] = true;
	while( bfsQueue.size() > 0 ) {
		int current = bfsQueue.front();
		bfsQueue.pop();
		visit( current );
		vector<int> adjList = graph.getNextVertices( current );
		for( int i = 0; i < adjList.size(); ++i ) {
			if( !visited[adjList[i]] ) {
				bfsQueue.push( adjList[i] );
				visited[adjList[i]] = true;
			}
		}
	}
}

int run_arc(std::istream& input, std::ostream& output) {
	int v;
	input >> v;

	IGraph* g = new ArcGraph(v);
	int n;
	input >> n;

	for (int i = 0; i < n; ++i) {
		int from;
		int to;
		input >> from >> to;
		g->addEdge(from, to);
	}

	BFS( *g, 2, [&output]( int v ) { output << v << " "; } );
	output << std::endl;
	
}

int run_list(std::istream& input, std::ostream& output) {
	int v;
	input >> v;

	IGraph* g = new ListGraph(v);
	int n;
	input >> n;

	for (int i = 0; i < n; ++i) {
		int from;
		int to;
		input >> from >> to;
		g->addEdge(from, to);
	}

	BFS( *g, 2, [&output]( int v ) { output << v << " "; } );
	output << std::endl;

	
	
}

int run_matrix(std::istream& input, std::ostream& output) {
	int v;
	input >> v;

	IGraph* g = new MatrixGraph(v);
	int n;
	input >> n;

	for (int i = 0; i < n; ++i) {
		int from;
		int to;
		input >> from >> to;
		g->addEdge(from, to);
	}

	BFS( *g, 2, [&output]( int v ) { output << v << " "; } );
	output << std::endl;

	
	
}

int run_set(std::istream& input, std::ostream& output) {
	int v;
	input >> v;

	IGraph* g = new SetGraph(v);
	int n;
	input >> n;

	for (int i = 0; i < n; ++i) {
		int from;
		int to;
		input >> from >> to;
		g->addEdge(from, to);
	}

	BFS( *g, 2, [&output]( int v ) { output << v << " "; } );
	output << std::endl;	
}

void testGraphs()
{
	// check same tests
	// list graph
	{
		std::stringstream input;
		std::stringstream output;
		input << "6 8 1 3 2 1 2 3 2 4 3 4 4 5 5 3 5 4";
		run_list(input, std::cout);
		// assert(output.str() == "2 1 3 4 5 \n");
	}

	// set graph
	{
		std::stringstream input;
		std::stringstream output;
		input << "6 8 1 3 2 1 2 3 2 4 3 4 4 5 5 3 5 4";
		run_set(input, std::cout);
		// assert(output.str() == "2 1 3 4 5 \n");
	}

	// matrix graph
	{
		std::stringstream input;
		std::stringstream output;
		input << "6 8 1 3 2 1 2 3 2 4 3 4 4 5 5 3 5 4";
		run_set(input, std::cout);
		// assert(output.str() == "2 1 3 4 5 \n");
	}

	// arc graph
	{
		std::stringstream input;
		std::stringstream output;
		input << "6 8 1 3 2 1 2 3 2 4 3 4 4 5 5 3 5 4";
		run_set(input, std::cout);
		// assert(output.str() == "2 1 3 4 5 \n");
	}
}

int main()
{
	testGraphs();
	return 0;
}