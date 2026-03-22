#include <iostream>

struct Array {
    int* data;
    int size;

    Array(int s) {
        size = s;
        data = new int[size];
    }

    ~Array() {
        delete[] data;
    }
};

int main() {
    Array arr(5);
    arr.data[0] = 10;
    arr.data[1] = 20;
    arr.data[2] = 30;
    arr.data[3] = 40;
    arr.data[4] = 50;

    for (int i = 0; i < arr.size; ++i) {
        std::cout << arr.data[i] << " ";
    }

    std::cout << "\n";
    return 0;
}