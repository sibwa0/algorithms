#include <vector>
#include <sstream>
#include <cassert>
#include <iostream>

struct StringHasher {
	unsigned int operator()( const std::string& key ) const {
		unsigned int hash = 0;
		for( unsigned int i = 0; i < key.length(); ++i )
			hash = hash * 137 + key[i];
		return hash;
	}
};

enum CellState {
    Empty,
    Key,
    Deleted
};


template<typename T, typename Hasher>
class HashTable {
public:
    HashTable(unsigned int init_size, const Hasher& hasher);
    ~HashTable();

    bool has(const T& key) const;
    bool add(const T& key);
    bool del(const T& key);

private:
    struct HashTableCell {
        T _key;
        CellState _state;
        unsigned int _hash;

        HashTableCell() : _key(0), _hash(0), _state(CellState::Empty) {}
        HashTableCell(
            T key = 0,
            unsigned int hash = 0,
            CellState state = CellState::Empty
        ) _key(key), _hash(hash), _state(state) {}
    };

    Hasher hasher;
    std::vector<HashTableCell> table;
    unsigned int del_count;
    unsigned int keys_count;


    void grow_table();

};

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::has(const T& key) const {
    unsigned int hash = hasher(key) % table.size();
    
    unsigned int i = 0;
    while (table[hash]._state != CellState::Empty && table[hash]._key != key) {
        hash += i mod m; 
    }
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::add(const T& key) {

}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::del(const T& key) {

}

template<typename T, typename Hasher>
void HashTable<T, Hasher>::grow_table() {

}




int run(std::istream& input, std::ostream& output) {
    StringHasher hasher;
    HashTable<std::string, StringHasher> table(8, hasher);
    char operation;
    std::string word;
    while (input >> operation >> word) {
        if(operation == '+')
			output << (table.add( word ) ? "OK" : "FAIL") << std::endl;
		if( operation == '?' )
			output << (table.has( word ) ? "OK" : "FAIL") << std::endl;
		if( operation == '-' )
			output << (table.del( word ) ? "OK" : "FAIL") << std::endl;
    }
    return 0;
}

void testHashTable() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "+ hello + bye ? bye + bye - bye ? bye ? hello";
        run(input, std::cout);
        // assert(output.str() == "OK\nOK\nOK\nFAIL\nOK\nFAIL\nOK\n");
    }
}

int main() {
    run(std::cin, std::cout);
    // testHashTable();
    return 0;
}