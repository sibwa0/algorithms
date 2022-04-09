#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>

#define DEFAULT_SIZE 5

template<typename T>
class CArray {
public:
    CArray(T* _arr = nullptr, int _size = 0, int _capacity = 0) : arr(_arr), size(_size), capacity(_capacity) {}

    int getSize() const { return size; }
    T& getArr() { return arr; }
    T getAt(int index) const;
    T operator[](int index) const { return getAt(index); }
    T& operator[](int index) { return getAt(index); }

    void add(const T& value);
    void resize();

    ~CArray() = default;

private:
    T* arr;
    int size;
    int capacity;

};

template<typename T>
T CArray<T>::getAt(int index) const {
    assert(index > 0 && index <= size && arr != 0);
    return arr[index];
}

template<typename T>
void CArray<T>::resize() {
    int new_capacity = std::max(capacity * 2, DEFAULT_SIZE);
    T* new_arr = new T[new_capacity];
    for (int i = 0; i < size; ++i) {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    capacity = new_capacity;
    arr = new_arr;
}

template<typename T>
void CArray<T>::add(const T& value) {
    if (capacity == size) {
        resize();
    }
    assert(arr != nullptr);
    arr[size++] = value;
}

// template<typename T>
// CArray<T>::~CArray() {
//     if (arr) {
//         delete[] arr;
//     }
// }

template<typename T>
class Queue {
public:
    Queue() : c_arr(), head(0), tail(0) {};
    Queue(const Queue&) = delete;
    ~Queue();

    Queue& operator=(const Queue&) = delete;

    void pushBack(const T& value);
    T popFront();
    int getSize() const { return c_arr.getSize(); }
    bool isEmpty() const { return c_arr.getSize() == 0; }

private:
    CArray c_arr;
    // struct {
    //     T* arr;
    //     int size;
    //     int capacity;
    // } c_arr;

    int head;
    int tail;

    void putTailToEnd();
};

template<typename T>
void Queue<T>::putTailToEnd() {
    
}

template<typename T>
void Queue<T>::pushBack(const T& value) {
    if (c_arr.getSize() == 0) {
        c_arr.add(value);
        ++head;
    } else if (head != tail) {
        c_arr[head++] = value;
        if (head == c_arr.getSize()) {
            head %= c_arr.getSize();
        }
    } else if (head == tail) {
        tail += size;
        c_arr.resize();
    }

}

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
    testFindIn();
    run(std::cin, std::cout);
    return 0;
}