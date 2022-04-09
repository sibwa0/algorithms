#include <iostream>
#include <sstream>
#include <cassert>

void testHeap() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 1 6 2 50 90 3 1 10 70";
        run(input, output);
        assert(output.str() == "1 6 10 50 70 90");
    }
}

int run(std::istream& input, std::ostream& output) {
    int k = 0;
    output << "Введите кол-во массивов" << std::endl;
    input >> k;

    int* pArr[k];
    for (int i = 0; i < k; ++i) {
        int size = 0;
        output << "Введите кол-во элементов массива " << i << std::endl;
        input >> size;
        pArr[i] = new int[size];
        
    }
}

int main() {
    testHeap();
    // run(std::cin, std::cout);
    return 0;
}