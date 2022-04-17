#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>

#define DEFAULT 2

template<typename T>
class CArray {
public:
    CArray( T* _array = nullptr,
            int _size = 0,
            int _capacity = 0) : array(_array), size(_size), capacity(_capacity) {}
    
    ~CArray() = default;

    T getAt(int index) const;
    T operator[](int index) const { return getAt(index); }
    T& operator[](int index) { assert(index > 0 && index <= size && array != nullptr); return array[index]; }

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

private:
    T* array;
    int size;
    int capacity;

    void resize();
};

template<typename T, typename Compare>
class Heap {
public:
    Heap(   CArray _array(nullptr, 0, 0),
            Compare _cmp) : array(_array), cmp(_cmp) {}
    Heap(const Heap&) = delete;
    ~Heap();

    Heap& operator=(const Heap&) = delete;

    T extractMin();
	const T& peekMin() const;
	void replaceMin(const T& el);	
	void insert(const T& el);	


private:
    CArray array;
    Compare cmp;
    

};




template<typename T>
T CArray<T>::getAt(int index) const {
    assert(index > 0 && index <= size && array != nullptr);
    return array[index];
}

template<typename T, typename Compare>
Heap<T, Compare>::~Heap() {
    if (array != nullptr) {
        delete[] array;
    }
}


// need fix
template<typename T>
void CArray<T>::resize() {
    int new_capacity = std::max(DEFAULT, capacity * 2);
    T* new_array = new T[new_capacity];
    if (capacity != 0) {
        int prev_head = head;
        head += capacity;
        for (int i = head; i < new_capacity; ++i) {
            new_array[i] = array[prev_head++];
        }
        for (int i = 0; i < tail; ++i) {
            new_array[i] = array[i];
        }
    }
    delete[] array;
    array = new_array;
    capacity = new_capacity;
}


int run(std::istream& input, std::ostream& output) {

    return 0;
}

void testHeap() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 3 44 3 50 2 44";
        run(input, output);
        assert(output.str() == "YES");
    }

}

int main() {
    testHeap();
    // run(std::cin, std::cout);

    return 0;
}