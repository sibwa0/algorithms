#include <vector>
#include <iostream>
#include <cassert>
using std::vector;
using std::string;

struct StringHasher {
	unsigned int operator()( const string& key ) const {
		unsigned int hash = 0;
		for( unsigned int i = 0; i < key.length(); ++i )
			hash = hash * 137 + key[i];
		return hash;
	}
};

template<class T, class H>
class HashTable {
public:
	HashTable( int initSize, const H& hasher );
	~HashTable();

	// Empty: return false
	// Key: key == Key ? return true : пробируемся дальше
	// Deleted: пробируемся дальше
	bool Has( const T& key ) const;
	// Empty: вствляем ключ либо в ранее найденную Deleted либо в текущую Empty
	// Key: key == Key ? return false : пробируемся дальше
	// Deleted: запоминаем первую повстречавшуюся Deleted, пробируемся дальше
	bool Add( const T& key );
	// Empty: return false
	// Key: key == Key ? помеаем Deleted и return true : пробируемся дальше
	// Deleted: пробируемся дальше
	bool Delete( const T& key );

private:
	struct HashTableNode {
		T Key;
		// TCellState = Empty / Key / Deleted
		unsigned int Hash;
		HashTableNode* Next;

		HashTableNode() : Next( nullptr ), Hash( 0 ) {}
		HashTableNode( const T& key, unsigned int hash, HashTableNode* next ) :
			Key( key ), Hash( hash ), Next( next ) {}
	};
	H hasher;
	// vector<HashTableCell> table;
	vector<HashTableNode*> table;
	unsigned int keysCount;

	void growTable();
};

template<class T, class H>
HashTable<T, H>::HashTable( int initSize, const H& _hasher ) :
	hasher( _hasher ),
	table( initSize, nullptr ),
	keysCount( 0 )
{
}

template<class T, class H>
HashTable<T, H>::~HashTable()
{
	for( unsigned int i = 0; i < table.size(); ++i ) {
		HashTableNode* node = table[i];
		while( node != nullptr ) {
			HashTableNode* nextNode = node->Next;
			delete node;
			node = nextNode;
		}
	}
}

template<class T, class H>
bool HashTable<T, H>::Has( const T& key ) const
{
	unsigned int hash = hasher( key ) % table.size();
	HashTableNode* node = table[hash];
	while( node != nullptr && node->Key != key ) {
		node = node->Next;
	}
	return node != nullptr;
}

template<class T, class H>
bool HashTable<T, H>::Add( const T& key )
{
	if( keysCount > 3 * table.size() ) {
		growTable();
	}

	unsigned int absHash = hasher( key );
	unsigned int hash = absHash % table.size();
	HashTableNode* node = table[hash];
	while( node != nullptr && node->Key != key ) {
		node = node->Next;
	}

	if( node != nullptr ) {
		return false;
	}

	table[hash] = new HashTableNode( key, absHash, table[hash] );
	++keysCount;
	return true;
}

template<class T, class H>
bool HashTable<T, H>::Delete( const T& key )
{
	unsigned  int hash = hasher( key ) % table.size();
	HashTableNode* node = table[hash];
	HashTableNode* prevNode = nullptr;
	while( node != nullptr && node->Key != key ) {
		prevNode = node;
		node = node->Next;
	}

	if( node == nullptr ) {
		return false;
	}

	if( prevNode == nullptr ) {
		table[hash] = node->Next;
	} else {
		prevNode->Next = node->Next;
	}

	delete node;
	--keysCount;
	return true;
}

template<class T, class H>
void HashTable<T, H>::growTable()
{
	vector<HashTableNode*> newTable( table.size() * 2, nullptr );
	for( unsigned int i = 0; i < table.size(); ++i ) {
		HashTableNode* node = table[i];
		while( node != nullptr ) {
			HashTableNode* nextNode = node->Next;
			int newHash = node->Hash % newTable.size();
			node->Next = newTable[newHash];
			newTable[newHash] = node;
			node = nextNode;
		}
	}
	table = std::move( newTable );
}

int main()
{
	StringHasher h;
	HashTable<string, StringHasher> table( 8, h );
	char operation;
	string word;
	while( std::cin >> operation >> word ) {
		if( operation == '+' )
			std::cout << (table.Add( word ) ? "OK" : "FAIL") << std::endl;
		if( operation == '?' )
			std::cout << (table.Has( word ) ? "OK" : "FAIL") << std::endl;
		if( operation == '-' )
			std::cout << (table.Delete( word ) ? "OK" : "FAIL") << std::endl;
	}
	return 0;
}