/*
Во всех задачах необходимо использование битовых операций. 
Использование арифметических операций запрещено.
Входное число лежит в диапазоне 0..2^32 -1 и вводится в десятичном виде.

1.3 Если в числе содержится только один бит со значением 1, записать в выходной поток OK. Иначе записать FAIL 
*/


#include <iostream>
#include <cassert>

int is_1bit_in_number(signed long num) {
    assert(num >= 0);

    int cnt = 0;

    while (num) {
        if (num & 1) {
            if (cnt == 0) {
                cnt = 1;
            } else {
                return -1;
            }
        }

        num >>= 1;
    }

    if (cnt == 1) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    signed long number = 0;
    std::cin >> number;

    if (!is_1bit_in_number(number)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }

    return 0;
}