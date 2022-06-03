#include "arc_graph.h"
#include "list_graph.h"
#include "matrix_graph.h"
#include "set_graph.h"

void BFS( const IGraph& graph, int vertex, void (*visit)(int) )
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

int main()
{
    IGraph* g = new ArcGraph(6);
	g->addEdge( 1, 3 );
	g->addEdge( 2, 1 );
	g->addEdge( 2, 3 );
	g->addEdge( 2, 4 );
	g->addEdge( 3, 4 );
	g->addEdge( 4, 5 );
	g->addEdge( 5, 3 );
	g->addEdge( 5, 4 );
	BFS( *g, 2, []( int v ) {std::cout << v << ", "; } );
	delete g;
}