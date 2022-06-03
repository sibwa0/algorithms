#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
#include <vector>

#define DEFAULT 2

// template<typename T>
// class CArray {
// public:
//     CArray( T* _array = nullptr,
//             int _size = 0,
//             int _capacity = 0) : array(_array), size(_size), capacity(_capacity) {}
    
//     ~CArray() = default;

//     T getAt(int index) const;
//     T operator[](int index) const { return getAt(index); }
//     T& operator[](int index) { assert(index > 0 && index <= size && array != nullptr); return array[index]; }

//     int getSize() const { return size; }
//     int getCapacity() const { return capacity; }
//     bool isEmpty() const { return size == 0; }

// private:
//     T* array;
//     int size;
//     int capacity;

//     void Resize();
// };

template<typename T>
class DefaultComparator {
public:
    bool operator()(const T& l, const T& r) { return l < r; }
};

template<typename T>
class isLessElement {
public:
    bool operator()(const T& l, const T& r) { return l.value < r.value; }
};

template<typename T, typename Compare = DefaultComparator<T>>
class Heap {
public:
    // Heap(CArray _array(nullptr, 0, 0), Compare _cmp) :
    //         array(_array), cmp(_cmp) {}
    Heap(size_t _capacity) : size(0), capacity(_capacity), cmp(Compare()) {
        array = new T[capacity];
    }
    Heap(T* _array = nullptr, size_t _size = 0, size_t _capacity = 0, Compare _cmp = Compare()) : array(_array), size(_size), capacity(_capacity), cmp(_cmp) {}
    Heap(const Heap&) = delete;
    ~Heap() {
        delete[] array;
    }

    // array
    T operator[](int index) const { return array[index]; }
    T& operator[](int index) { return array[index]; }
    size_t Size() const { return size; }

    Heap& operator=(const Heap&) = delete;

    T ExtractMin() {
        assert(size != 0);
        T result = array[0];
        std::swap(array[size - 1], array[0]);
        --size;
        if (size != 0) {
            SiftDown(0);
        }
        return result;
    }
	const T& PeekMin() const { return array[0]; }
	// void replaceMin(const T& el);	
	void Insert(const T& el) {
        if (size == capacity) {
            Resize();
        }
        array[0].value = 0;
        array[size] = el;
        SiftUp(size);
        ++size;
    }


private:
    // CArray array[];
    T* array;
    size_t size;
    size_t capacity;
    Compare cmp;
    
    // without using CArray
    void Resize() {
        size_t new_capacity = std::max((size_t)DEFAULT, capacity * 2);
        T* new_array = new T[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        capacity = new_capacity;
    }

    // Heap
    void SiftUp(size_t index, Compare cmp = Compare()) {
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
    
    void SiftDown(size_t index, Compare cmp = Compare()) {
        size_t min_leaf = 0;
        // mb shoude be "<"
        while ((index <= size / 2 - 1) /*&& (cmp(array[index], array[2 * index - 1]) || cmp(array[index], array[2 * index - 2]))*/) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            if (left > capacity && right > capacity) {
                return;
            } else if (left > capacity) {
                
            }
            if (cmp(array[index], array[left]) && cmp(array[index], array[right])) {
                return;
            }
            if (cmp(array[left], array[right])) {
                min_leaf = left;
            } else {
                min_leaf = right;
            }
            std::swap(array[index], array[min_leaf]);
            index = min_leaf;
        }
    }

    void Build() {
        for (ssize_t i = size / 2 - 1; i >= 0; --i) {
            SiftDown(i);
        }
    }
};


// template<class T, class Compare = IsLess<T> >
// void MegaSort( T* array, int l, int r, Compare cmp = IsLess<T>() )// bool (*isLess)( const T&, const T& ) = IsLessDefault )
// {
// 	for( int i = l; i < r; ++i ) {
// 		for( int j = l; j < r; ++j ) {
// 			if( cmp( array[j + 1], array[j] ) ) {
// 				std::swap( array[j], array[j + 1] );
// 			}
// 		}
// 	}
// }


// template<typename T, typename Compare>
// T Heap<T, Compare>::ExtractMin() {
//     assert(size != 0);
//     T result = array[0];
//     std::swap(array[size - 1], array[0]);
//     --size;
//     if (size != 0) {
//         SiftDown(0);
//     }
//     return result;
// }

// template<typename T, typename Compare>
// const T& Heap<T, Compare>::PeekMin() const {
//     return array[0];
// }

// high attention to Compare
// template<typename T, typename Compare>
// void Heap<T, Compare>::SiftUp(size_t index, Compare cmp) {
//     while (index > 0) {
//         size_t parent = (index - 1) / 2;
//         if (cmp(array[index], array[parent])) {
//             std::swap(array[(index - 1) / 2], array[index]);
//             index = parent;
//         } else {
//             return;
//         }
//     }
// }

// template<typename T, typename Compare>
// void Heap<T, Compare>::Build() {
//     for (ssize_t i = size / 2 - 1; i >= 0; --i) {
//         SiftDown(i);
//     }
// }

template<typename T, typename Compare>
void Heap<T, Compare>::SiftDown(size_t index, Compare cmp) {
    size_t min_leaf = 0;
    // mb shoude be "<"
    while ((index <= size / 2 - 1) /*&& (cmp(array[index], array[2 * index - 1]) || cmp(array[index], array[2 * index - 2]))*/) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        if (left > capacity && right > capacity) {
            return;
        } else if (left > capacity) {
            
        }
        if (cmp(array[index], array[left]) && cmp(array[index], array[right])) {
            return;
        }
        if (cmp(array[left], array[right])) {
            min_leaf = left;
        } else {
            min_leaf = right;
        }
        std::swap(array[index], array[min_leaf]);
        index = min_leaf;
    }
}

// template<typename T, typename Compare>
// void Heap<T, Compare>::Insert(const T& el) {
//     if (size == capacity) {
//         Resize();
//     }
//     array[size] = el;
//     SiftUp(size);
//     ++size;
// }

// template<typename T, typename Compare>
// void Heap<T, Compare>::Resize() {
//     size_t new_capacity = std::max((size_t)DEFAULT, capacity * 2);
//     T* new_array = new T[new_capacity];
//     for (int i = 0; i < size; ++i) {
//         new_array[i] = array[i];
//     }
//     delete[] array;
//     array = new_array;
//     capacity = new_capacity;
// }


template<class T, class Compare = DefaultComparator<T>>
void MergeSortedArrays(T** array, int* result, Compare cmp = DefaultComparator<T>()) {
	
}


// 5


// template<typename T>
// T CArray<T>::getAt(int index) const {
//     assert(index > 0 && index <= size && array != nullptr);
//     return array[index];
// }

// template<typename T, typename Compare>
// Heap<T, Compare>::~Heap() {
//     if (array != nullptr) {
//         delete[] array;
//     }
// }


// // need fix
// template<typename T>
// void CArray<T>::Resize() {
//     int new_capacity = std::max(DEFAULT, capacity * 2);
//     T* new_array = new T[new_capacity];
//     if (capacity != 0) {
//         int prev_head = head;
//         head += capacity;
//         for (int i = head; i < new_capacity; ++i) {
//             new_array[i] = array[prev_head++];
//         }
//         for (int i = 0; i < tail; ++i) {
//             new_array[i] = array[i];
//         }
//     }
//     delete[] array;
//     array = new_array;
//     capacity = new_capacity;
// }


// int run(std::istream& input, std::ostream& output) {

//     return 0;
// }

// void testHeap() {
//     {
//         std::stringstream input;
//         std::stringstream output;
//         input << "3 1 6 2 50 90 3 1 10 70";
//         run(input, output);
//         assert(output.str() == "1 6 10 50 70 90");
//     }

// }


// class Cmp {

// };
struct Element {
    int value;
    size_t value_index;
    size_t array_index;
};

int main() {
    // testHeap();
    // run(std::cin, std::cout);
    size_t k = 0;
    std::cin >> k;
    // Element** p_arr = new Element*[k];

    std::vector<std::vector<Element>> pArr(k);
    Heap<Element, isLessElement<Element>> heap(k);

    size_t size_arr = 0;
    size_t size_arr_tmp = 0;
    for (size_t i = 0; i < k; ++i) {
        std::cin >> size_arr_tmp;
        // p_arr[i] = new Element[size_arr_tmp]; 
        size_arr += size_arr_tmp;
        int value = 0;
        pArr[i].resize(size_arr_tmp);
        for (size_t j = 0; j < size_arr_tmp; ++j) {
            std::cin >> value;
            pArr[i][j].value = value;
            pArr[i][j].array_index = i;
            pArr[i][j].value_index = j;
        }
        Element tmp = pArr[i][0];
        heap.Insert(tmp);
    }


    std::cout << std::endl;
    for (size_t i = 0; i < k; ++i) {
        for (size_t j = 0; j < pArr[i].size(); ++j) {
            std::cout << pArr[i][j].value << ":" << pArr[i][j].value_index << "," << pArr[i][j].array_index << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;


    int* result = new int[size_arr];

    std::cout << heap.PeekMin().value << std::endl;
    heap.ExtractMin();
    std::cout << heap.PeekMin().value << std::endl;
    heap.ExtractMin();
    // MergeSort(pArr, result);
    // for (size_t i = 0; i < size_arr; ++i) {
    //     std::cout << result[i] << " ";
    // }



    delete[] result;
    return 0;
}