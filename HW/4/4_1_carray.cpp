#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
#include <vector>

#define DEFAULT 2

template<typename T>
class CArray {
public:
    CArray( T* _array = nullptr,
            size_t _size = 0,
            size_t _capacity = 0) : array(_array), size(_size), capacity(_capacity) {}
    
    CArray(size_t _capacity) : size(0), capacity(_capacity) { array = new T[capacity]; }
    
    ~CArray() = default;

    T getAt(int index) const { return array[index]; }
    T operator[](int index) const { return getAt(index); }
    T& operator[](int index) {
        assert(index >= 0);
        assert(index <= capacity);
        assert(array != nullptr);
        return array[index];
    }
    void add(T value) {
        if (size == capacity) {
            resize();
        }
        array[size] = value;
        ++size;
    }

    size_t getSize() const { return size; }
    void increaseSizeByOne() { ++size; }
    void decreaseSizeByOne() { --size; }
    size_t getCapacity() const { return capacity; }
    bool isEmpty() const { return size == 0; }
    void resize();
    void resize(size_t new_capacity);

private:
    T* array;
    size_t size;
    size_t capacity;

};

template<typename T>
void CArray<T>::resize() {
    size_t new_capacity = std::max((size_t)DEFAULT, capacity * 2);
    T* new_array = new T[new_capacity];
    for (int i = 0; i < size; ++i) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
    capacity = new_capacity;
}

template<typename T>
void CArray<T>::resize(size_t new_capacity) {
    T* new_array = new T[new_capacity];
    for (int i = 0; i < size; ++i) {
        new_array[i] = array[i];
    }
    if (array != nullptr) {
        delete[] array;
    }
    array = new_array;
    capacity = new_capacity;
}


template<typename T>
class isLessDefault {
public:
    bool operator()(const T& l, const T& r) { return l < r; }
};

template<typename T>
class isLessElement {
public:
    bool operator()(const T& l, const T& r) { return l.value < r.value; }
};


template<typename T, typename Compare = isLessDefault<T>>
class Heap {
public:
    Heap(CArray<T> _array = {nullptr, 0, 0}) : array(_array), cmp(Compare()) {}

    Heap(const Heap&) = delete;
    ~Heap() {}

    T extractMin() {
        assert(array.getSize() != 0);
        T result = array[0];
        std::swap(array[array.getSize() - 1], array[0]);
        array.decreaseSizeByOne();
        if (array.getSize() != 0) {
            siftDown(0);
        }
        return result;
    }
	T peekMin() const {
        assert(array.getSize() != 0);
        return array[0];
    }

	void insert(const T& el) {
        if (array.getSize() == array.getCapacity()) {
            array.resize();
        }
        array[array.getSize()] = el;
        siftUp(array.getSize());
        array.increaseSizeByOne();
    }

private:
    CArray<T> array;
    Compare cmp;

    // Heap
    void siftUp(size_t index, Compare cmp = Compare()) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (cmp(array[index], array[parent])) {
                std::swap(array[(index - 1) / 2], array[index]);
                index = parent;
            } else {
                return;
            }
        }
    }
    
    void siftDown(size_t index, Compare cmp = Compare()) {
        size_t min_leaf = 0;
        while (index <= array.getSize() / 2 - 1) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;

            // case child exeption 
            if (right >= array.getSize()) {
                if (left == array.getSize() - 1 && cmp(array[left], array[index])) {
                    min_leaf = left;
                } else {
                    return;
                }
            } else {
                // case end of sift
                if (cmp(array[index], array[left]) && cmp(array[index], array[right])) {
                    return;
                }

                // find which child swap with parent
                if (cmp(array[left], array[right])) {
                    min_leaf = left;
                } else {
                    min_leaf = right;
                }
            }
            std::swap(array[index], array[min_leaf]);
            index = min_leaf;
        }
    }

    void build() {
        for (ssize_t i = array.getSize() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

};


struct Element {
    int value;
    size_t value_index;
    size_t array_index;
};

void SortArrays(CArray<CArray<Element>> array, int* result, size_t full_array_size) {
    Heap<Element, isLessElement<Element>> heap(array.getCapacity());

	for (size_t i = 0; i < array.getCapacity(); ++i) {
        heap.insert(array[i][0]);
    }
    for (size_t i = 0; i < full_array_size; ++i) {
        Element tmp = heap.extractMin();
        result[i] = tmp.value;
        if (tmp.value_index < array[tmp.array_index].getCapacity() - 1) {
            heap.insert(array[tmp.array_index][tmp.value_index + 1]);
        }
    }
}

int run(std::istream& input, std::ostream& output) {
    size_t k = 0;
    input >> k;
    CArray<CArray<Element>> p_arr(k);

    int tmp_size = 0;
    size_t full_array_size = 0;
    for (size_t i = 0; i < k; ++i) {
        input >> tmp_size;
        p_arr[i].resize(tmp_size);
        full_array_size += p_arr[i].getCapacity();
        int value = 0; 
        for (size_t j = 0; j < tmp_size; ++j) {
            input >> value;
            p_arr[i][j].value = value;
            p_arr[i][j].value_index = j;
            p_arr[i][j].array_index = i;
            p_arr[i].increaseSizeByOne();
        }
    }

    int* result = new int[full_array_size];
    SortArrays(p_arr, result, full_array_size);
    for (size_t i = 0; i < full_array_size; ++i) {
        output << result[i] << " ";
    }
    delete[] result;


    return 0;
}

void testHeap() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 1 6 2 50 90 3 1 10 70";
        run(input, output);
        assert(output.str() == "1 6 10 50 70 90 ");
    }
}


int main() {
    // testHeap();
    run(std::cin, std::cout);
}
