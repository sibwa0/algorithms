#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>

int find_nearest_indexes(int A[], int A_size, int B[], int B_size, int res[], int res_size) {
    assert(A_size > 0);
    assert(B_size > 0);
    assert(B_size == res_size);

    for (int i = 0; i < B_size; ++i) {
        // if B[i] is out of range, then res[i] equals extreme case
        if (B[i] < A[0]) {
            res[i] = 0;
        } else if (B[i] > A[A_size - 1]) {
            res[i] = A_size - 1;
        } else {
            // exponential step
            int power = 0;
            int first = 0;
            int last = pow(2, power);
            while (last < A_size) {
                if  (B[i] > A[last]) {
                    ++power;
                    first = last;
                    last = pow(2, power);
                    if (last > A_size - 1) {
                        last = A_size - 1;
                    }
                } else {
                    // binary search; B[i] is placed between two desired elems: fistt and last
                    while (first < last && (last - first != 1)) {
                        int mid = (first + last) / 2;
                        if (A[mid] < B[i]) {
                            first = mid;
                        } else {
                            last = mid;
                        }
                    }
                    // find the shortest distance between first and   
                    if (A[last] - B[i] < B[i] - A[first]) {
                        res[i] = last;
                    } else {
                        res[i] = first;
                    }
                    break;
                }
            }
        }
    }

    return 0;
}


int run(std::istream& input, std::ostream& output) {
    output << "Введите кол-во элементов А: " << std::endl;
    int n = 0;
    input >> n;
    int* A = new int[n];
    output << "Введите элементы: " << std::endl;
    for (int i = 0; i < n; ++i) {
        input >> A[i];
    }

    output << "Введите кол-во элементов B: " << std::endl;
    int m = 0;
    input >> m;
    int* B = new int[m];
    output << "Введите элементы: " << std::endl;
    for (int j = 0; j < n; ++j) {
        input >> B[j];
    }

    int* res = new int[m];

    if (!find_nearest_indexes(A, n, B, m, res, m)) {
        for (int i = 0; i < m; ++i) {
            output << res[i] << " ";
        }
        output << std::endl;
    }

    delete[] A;
    delete[] B;
    delete[] res;

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
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 10 20 30 3 9 18 35";
        run(input, output);
        assert(output.str() == "0 1 2 ");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 10 20 30 4 8 9 10 32";
        run(input, output);
        assert(output.str() == "0 0 0 2 ");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "11 10 20 30 40 50 60 70 80 90 100 110 4 8 32 68 150";
        run(input, output);
        assert(output.str() == "0 2 6 10 ");
    }
    
}

int main() {
    testFindIn();
    // run(std::cin, std::cout);
    return 0;
}