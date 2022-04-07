#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>

template<typename T>
class CArray {
public:
    CArray(T* _array = nullptr, int _size = 0, int _capacity = 0) : array(_array), size(_size), capacity(_capacity) {}

    int size() const { return size; }
    T get_at(int index) const;
    T operator[](int index) const { return get_at(index); }
    T& operator[](int index);

private:
    T* array;
    int size;
    int capacity;
};

template<typename T>
T CArray<T>::get_at(int index) const {
    assert(index > 0 && index <= size && array != 0);
    return array[index];
}

template<typename T>
class Queue {
public:
    Queue() = default;
    Queue(const Queue&) = delete;
    ~Queue();

    Queue& operator = ( const Queue& ) = delete;

    void push_back(const T& value);
    T pop_front();
    int size() const { return size; }
    bool is_empty() const { return size == 0; }

private:
    
};

int run(std::istream& input, std::ostream& output) {

    return 0;
}

void testFindIn() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 10 20 30 3 9 15 35";
        run(input, output);
        assert(output.str() == "0 0 2 ");
    }
}

int main() {
    // testFindIn();
    run(std::cin, std::cout);
    return 0;
}