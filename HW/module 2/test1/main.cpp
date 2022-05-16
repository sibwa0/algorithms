#include <vector>
#include <sstream>
#include <cassert>
#include <iostream>

class StringHasher {
public:
	unsigned int operator()(const std::string& key) const {
		unsigned int hash = 0;
		for (auto c : key) {
			hash = hash * 37 + c;
        }
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
    HashTable(unsigned int _init_size, const Hasher& _hasher) :
        hasher(_hasher),
        table(_init_size),     
        keys_count(0)
    {
    }
    ~HashTable() = default;

    bool has(const T& key) const;
    bool add(const T& key);
    bool del(const T& key);

private:
    struct HashTableCell {
        T key;
        CellState state;
        unsigned int hash_value;

        HashTableCell() : state(CellState::Empty), hash_value(0) {}
        HashTableCell(T _key, CellState _state, unsigned int _hash_value) :
            key(_key),
            state(_state),
            hash_value(_hash_value)
        {
        }
    };

    Hasher hasher;
    std::vector<HashTableCell> table;
    unsigned int keys_count;

    void grow_table();

};

template<typename T, typename Hasher>
void HashTable<T, Hasher>::grow_table() {
    unsigned int new_size = table.size() == 0 ? 8 : table.size() * 2;
    std::vector<HashTableCell> new_table(new_size);

    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i].state == CellState::Key) {
            unsigned int hash = table[i].hash_value % new_size;

            for (size_t j = 0; ; ++j) {
                if (new_table[hash].state == CellState::Empty) {
                    new_table[hash].key = table[i].key;
                    new_table[hash].state = CellState::Key;
                    new_table[hash].hash_value = table[i].hash_value;
                    break;
                }
                hash = (hash + j + 1) % new_size;
            }
        }
    }

    table = std::move(new_table);
}


    // Empty: return false
	// Key: key == Key ? return true : пробируемся дальше
	// Deleted: пробируемся дальше
// bool Has( const T& key ) const;

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::has(const T& key) const {
    unsigned int hash = hasher(key) % table.size();
    
    unsigned int i = 0;
    for (size_t i = 0; i < table.size(); ++i) {

        if (table[hash].state == CellState::Empty) {
            return false;
        }
        else if (table[hash].state == CellState::Key && table[hash].key == key) {
            return true;
        }
        hash = (hash + i + 1) % table.size();
    }
    
    return false;
}


	// Empty: вствляем ключ либо в ранее найденную Deleted либо в текущую Empty
	// Key: key == Key ? return false : пробируемся дальше
	// Deleted: запоминаем первую повстречавшуюся Deleted, пробируемся дальше
// bool Add( const T& key );

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::add(const T& key) {
    if (keys_count >= table.size() * 0.75) {
        grow_table();
    }

    unsigned int hash_pos = hasher(key);
    unsigned int hash = hash_pos % table.size();
    unsigned int del_cell = -1;
    
    for (size_t i = 0; i < table.size(); ++i) {

        if (table[hash].state == CellState::Empty) {
            if (del_cell != -1) {
                hash = del_cell;
            }
            table[hash].state = CellState::Key;
            table[hash].key = key;
            table[hash].hash_value = hash_pos;
            ++keys_count;
            return true;
        }
        else if (table[hash].state == CellState::Key && table[hash].key == key) {
            return false;
        }
        else if (table[hash].state == CellState::Deleted && del_cell == -1) {
            del_cell = hash;
        }
        hash = (hash + i + 1) % table.size();
    }

    table[del_cell].key = key;
    table[del_cell].state = CellState::Key;
    table[del_cell].hash_value = hash_pos;
    ++keys_count;
    return true;
}


	// Empty: return false
	// Key: key == Key ? помеаем Deleted и return true : пробируемся дальше
	// Deleted: пробируемся дальше
// bool Delete( const T& key );

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::del(const T& key) {
    int hash = hasher(key) % table.size();

    for (size_t i = 0; i < table.size(); ++i) {

        if (table[hash].state == CellState::Empty) {
            return false;
        }
        else if (table[hash].state == CellState::Key && table[hash].key == key) {
            table[hash].state = CellState::Deleted;
            --keys_count;
            return true;
        }
        hash = (hash + i + 1) % table.size();
    }

    return false;
}



int run(std::istream& input, std::ostream& output) {
    StringHasher hasher;
    unsigned int table_size = 8;
    HashTable<std::string, StringHasher> table(table_size, hasher);
    
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
        run(input, output);
        assert(output.str() == "OK\nOK\nOK\nFAIL\nOK\nFAIL\nOK\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "+ h + he + hel + hell + hello + b + by + bye + n + ne + new ? b ? by";
        run(input, std::cout);
        // assert(output.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
    }
}

int main() {
    // run(std::cin, std::cout);
    testHashTable();
    return 0;
}