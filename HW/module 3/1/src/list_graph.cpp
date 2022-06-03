#include "list_graph.h"


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
