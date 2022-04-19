#include <iostream>
#include <sstream>
#include <cassert>

template<typename T>
class isLess {
public:
    bool operator()(const T& l, const T& r) {
        return l < r;
    }
};

template<typename T, typename Compare = isLess<T>>
int medium3_value(const T* array, const int& size, Compare cmp) {
    T start = 0;
    T mid = size / 2;
    T end = size - 1;
    if (cmp(array[end], array[start]) && cmp(array[start], array[mid]) ||
            cmp(array[mid], array[start]) && cmp(array[start], array[end])) {
        return start;
    } else if (cmp(array[start], array[mid]) && cmp(array[mid], array[end]) ||
            cmp(array[end], array[mid]) && cmp(array[mid], array[start])) {
        return mid;
    }
    return end;
}

template<typename T, typename Compare = isLess<T>>
int partition(T* array, int size, Compare cmp) {
    int pivot = medium3_value<T, Compare>(array, size, cmp);
    std::swap(array[pivot], array[size - 1]);
    pivot = size - 1;
    int i = 0;
    int j = 0;

    while (j <= size - 2) {
        if (cmp(array[pivot], array[j])) {
            j++;
        } else {
            std::swap(array[i], array[j]);
            i++;
            j++;
        }
    }
    std::swap(array[pivot], array[i]);
    return i;
}

template<typename T, typename Compare = isLess<T>>
int kStatMedium3(T* array, int size, int k, Compare cmp = Compare()) {
    int p = 0;

    do {
        p = partition<T, Compare>(array, size, cmp);
        if (k >= p) {
            array += p;
            size -= p; 
            k -= p;
        } else {
            size = p;
        }
    } while (size > 1);

    return array[0];
}

int run(std::istream& input, std::ostream& output) {
    int n = 0;
    input >> n;
    int* res_array = new int[n];
    for (int i = 0; i < n; i++) {
        input >> res_array[i];
    }

    int k10 = n * 10 / 100;
    int k50 = n * 50 / 100;
    int k90 = n * 90 / 100;

    output << kStatMedium3<int>(res_array, n, k10) << std::endl;
    output << kStatMedium3<int>(res_array, n, k50) << std::endl;
    output << kStatMedium3<int>(res_array, n, k90) << std::endl;
    delete[] res_array;

    return 0;
}

void testPart() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 1 2 3 4 5 6 7 8 9 10";
        run(input, output);
        assert(output.str() == "2\n6\n10\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 9 4 6 10 3 5 2 8 1 7";
        run(input, output);
        assert(output.str() == "2\n6\n10\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 5 6 7 8 9 1 2 3 4 10";
        run(input, output);
        assert(output.str() == "2\n6\n10\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 10 9 8 7 6 5 4 3 2 1";
        run(input, output);
        assert(output.str() == "2\n6\n10\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 10 9 8 7 6 5 4 3 2 1";
        run(input, output);
        assert(output.str() == "2\n6\n10\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 10 1 9 2 8 3 7 4 6 5";
        run(input, output);
        assert(output.str() == "2\n6\n10\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "4 3 4 2 1";
        run(input, output);
        assert(output.str() == "1\n3\n4\n");
    }
}

int main() {
    run(std::cin, std::cout);
    // testPart();

    return 0;
}