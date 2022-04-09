#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>

#define DEFAULT 2


/*
template<typename T>
class CArrayQueue {
public:
    CArrayQueue(T* _array = nullptr, int _size = 0, int _capacity = 0) : array(_array), size(_size), capacity(_capacity) {}

    int size() const { return size; }
    T get_at(int index) const;
    T operator[](int index) const { return get_at(index); }
    T& operator[](int index) { return get_at(index); };

private:
    T* array;
    int size;
    int capacity;

    void resize();
};
*/

template<typename T>
class Queue {
public:
    Queue(  T* _array = nullptr,
            int _size = 0,
            int _capacity = 0,
            int _head = 0,
            int _tail = 0) : array(_array), size(_size), capacity(_capacity), head(_head), tail(_tail) {}
    Queue(const Queue&) = delete;
    ~Queue();

    Queue& operator=(const Queue&) = delete;

    // CArray
    T getAt(int index) const;
    T operator[](int index) const { return getAt(index); }
    T& operator[](int index) { return getAt(index); };

    void pushBack(const T& value);
    T popFront();

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

private:
    T* array;
    int size;
    int capacity;
    int head;
    int tail;

    void resize();
};

template<typename T>
void Queue<T>::pushBack(const T& value) {
    // assert(array != nullptr);
    if (tail == head && size == capacity) {
        resize();
    }
    array[tail] = value;
    tail = (tail + 1) % capacity;
    ++size;
}

template<typename T>
T Queue<T>::getAt(int index) const {
    assert(index > 0 && index <= size && array != nullptr);
    return array[index];
}

template<typename T>
Queue<T>::~Queue() {
    if (!array) {
        delete[] array;
    }
}

template<typename T>
void Queue<T>::resize() {
    int new_capacity = std::max(DEFAULT, capacity * 2);
    T* new_array = new T[new_capacity];
    if (capacity != 0) {
        head += capacity;
        for (int i = head; i < new_capacity; ++i) {
            new_array[i] = array[i - head];
        }
        for (int i = 0; i < tail; ++i) {
            new_array[i] = array[i];
        }
    }
    delete[] array;
    array = new_array;
    capacity = new_capacity;
}


// int run(std::istream& input, std::ostream& output) {

//     return 0;
// }

// void testFindIn() {
//     {
//         std::stringstream input;
//         std::stringstream output;
//         input << "3 10 20 30 3 9 15 35";
//         run(input, output);
//         assert(output.str() == "0 0 2 ");
//     }
// }

int main() {
    // testFindIn();
    // run(std::cin, std::cout);
    Queue<int> q;
    q.pushBack(5);
    q.pushBack(15);
    q.pushBack(10);

    std::cout << q[2] << std::endl;

    return 0;
}