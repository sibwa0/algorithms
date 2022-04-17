#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>

int find_min_elem_index(std::vector<int> arr) {
    int first = 0;
    int last = arr.size();
    int min = std::min(arr[first], arr[last - 1]);
    while (first < last) {
        int mid = (first + last) / 2;
        if (arr[mid] > arr[mid + 1]) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }

    return first;
}

int run(std::istream& input, std::ostream& output) {
    int n = 0;
    input >> n;
    std::vector<int> arr(n);
    int elem = 0;
    for (int i = 0; i < arr.size(); ++i) {
        input >> elem;
        arr[i] = elem;
    }

    output << find_min_elem_index(arr);

    return 0;
}

void testFindIn() {
    // {
    //     std::stringstream input;
    //     std::stringstream output;
    //     input << "5 4 5 1 2 3";
    //     run(input, output);
    //     assert(output.str() == "2");
    // }
    {
        std::stringstream input;
        std::stringstream output;
        input << "8 12 14 16 17 1 3 5 7";
        run(input, output);
        assert(output.str() == "4");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "6 5 5 5 5 5 1";
        run(input, output);
        assert(output.str() == "5");
    }
}

int main() {
    testFindIn();
    // run(std::cin, std::cout);
    return 0;
}