//
// Created by MashaGuzhva on 22/03/2026.
//

#include "../../include/structures/Array.h"


// opisujemy, do czego służy ta funkcja z plika .h

//Constructor – saves the size and creates a dynamic array
Array::Array(int s) {
    size = s;
    data = new int[size];
}

// Destructor – removes arrays from memory, aby nie było memory leaks
Array::~Array() {
    delete[] data;
}
int Array::getSize() const { // Returns array size
    return size;
}

int& Array::id(int index) { // Returns element at given index
    return data[index];
}

