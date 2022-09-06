#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>

#define DEFAULT 2
#define POP_FRONT 2
#define PUSH_BACK 3

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
    T& operator[](int index) { assert(index > 0 && index <= size && array != nullptr); return array[index]; }

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
    if ((tail == head && size == capacity) || size == capacity) {
        resize();
    }
    array[tail] = value;
    tail = (tail + 1) % capacity;
    ++size;
}

template<typename T>
T Queue<T>::popFront() {
    // assert(size != 0 && array != nullptr);
    if (size == 0) {
        return -1;
    }
    int result = head;
    head = (head + 1) % capacity;
    --size;
    return array[result];
}

template<typename T>
T Queue<T>::getAt(int index) const {
    assert(index > 0 && index <= size && array != nullptr);
    return array[index];
}

template<typename T>
Queue<T>::~Queue() {
    if (array != nullptr) {
        delete[] array;
    }
}

template<typename T>
void Queue<T>::resize() {
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
    Queue<int> q;
    int n = 0;
    input >> n;
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        int option = 0;
        input >> option;
        int value = 0;
        input >> value;
        switch (option) {
            case (PUSH_BACK):
                q.pushBack(value);
                break;
            case (POP_FRONT):
                if ((q.isEmpty() && value != -1) || q.popFront() != value) {
                    flag = false;
                }
                break;
            default:
                break;
        }
    }
    if (flag) {
        output << "YES";
    } else {
        output << "NO";
    }
    return 0;
}

void testFindIn() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 3 44 3 50 2 44";
        run(input, output);
        assert(output.str() == "YES");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "2 2 -1 3 10";
        run(input, output);
        assert(output.str() == "YES");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "2 3 44 2 66";
        run(input, output);
        assert(output.str() == "NO");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "1 2 -1";
        run(input, output);
        assert(output.str() == "YES");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "11 3 1 3 2 3 3 3 4 3 5 2 1 2 2 2 3 2 4 2 5 2 -1";
        run(input, output);
        assert(output.str() == "YES");
    }
}

int main() {
    // testFindIn();
    run(std::cin, std::cout);

    return 0;
}