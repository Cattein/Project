#include <iostream>
#include "structures/Array.h"

int main() {
    // create a table of size 5
    Array arr(5);

    // wwrie a number of the table
    arr.setId(0) = 10;
    arr.setId(1) = 20;
    arr.setId(2) = 30;
    arr.setId(3) = 40;
    arr.setId(4) = 50;

    for (int i = 0; i < arr.getSize(); ++i) {
        std::cout << arr.setId(i) << " ";
    }

    std::cout << "\n";
    return 0;
}