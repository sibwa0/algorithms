#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <cstring>

template<typename T>
class isEqualDefault {
    bool operator()(const T& l, const T& r) {
        return l == r;
    }
};

template<typename T>
class isLessDefault {
    bool operator()(const T& l, const T& r) {
        return l <= r;
    }
};


template<typename T, typename Compare = isLessDefault<T>>
void merge(T* first, const T& first_len, T* second, const T& second_len, T* c, Compare cmp) {
    size_t i = 0;
    size_t j = 0;
    for (size_t cur = 0; cur < first_len + second_len; ++cur) {
        if (cmp(first[i], second[j])) {
            c[cur] = first[i];
            ++i;
            if (i == first_len) {
                std::copy(second + j, second + second_len, c + cur + 1);
            }
        } else {
            c[cur] = second[j];
            ++j;
            if (j == second_len) {
                std::copy(first + i, first + first_len, c + cur + 1);
            }
        }
    }
}


template<typename T, typename Compare = isLessDefault<T>>
void mergeSortRecursive( int* a, int a_len ) {
    if( a_len <= 1 ) {
        return;
    }
    int first_len = a_len / 2;
    int second_len = a_len - first_len;
    mergeSortRecursive<T, Compare>(a, first_len);
    mergeSortRecursive<T, Compare>(a + first_len, second_len);
    int* c = new int[a_len];
    merge<T, Compare>(a, first_len, a + first_len, second_len, c);
    std::memcpy(a, c, sizeof(T) * a_len);
    delete[] c;
}

template<typename T, typename Compare = isEqualDefault<T>>
size_t find_one_layer(T* start, T* end, size_t size, Compare cmp) {
    mergeSortRecursive<T, Compare>(start, size);
    mergeSortRecursive<T, Compare>(end, size);

    size_t str_size = std::max(start[size - 1], end[size - 1]);
    size_t i = 0;
    size_t j = 0;
    int len_one_layer = 0;
    int cur_num_layer = 0;
    for (size_t k = std::min(start[0], end[0]); k <= str_size + 1; ++k) {
        if (cur_num_layer == 1) {
            ++len_one_layer;
        }

        if (i != size && start[i] == k) {
            ++cur_num_layer;
            ++i;
        }
        if (i != size && end[j] == k) {
            --cur_num_layer;
            ++j;
        }
    }

    return len_one_layer;
}

int run(std::istream& input, std::ostream& output) {
    size_t n = 0;
    input >> n;

    int* start = new int[n];
    int* end = new int[n];

    int start_el = 0;
    int end_el = 0;

    for (size_t i = 0; i < n; ++i) {
        input >> start_el;
        start[i] = start_el;

        input >> end_el;
        end[i] = end_el;
    }

    output << find_one_layer<int, isEqualDefault<int>>(start, end, n) << std::endl;

}

void testMergeSort() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 1 4 7 8 2 5";
        run(input, std::cout);
        // assert(output.str() == "3")
    }
}

int main() {
    // run(std::cin, std::cout);
    testMergeSort();
}
