//
// Created by MariiaHuzhva on 22/03/2026.
//

#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H
// Dynamic array
class Array {
private:
    int* data;   // Pointer to the array
    int size;    // Number of array elements

public:
    Array(int size);  // Constructor - creates array
    ~Array();         // Destructor - frees memory

    int getSize() const { // Returns array size
        return size;
    }

    bool empty() const { // Checks if array is empty
        return size == 0;
    }

    int& setId(int index) { // Returns element at given index
        return data[index];
    }

    const int& setId(int index) const { // Const version
        return data[index];
    }

    bool get(int index, int& value) const; // Reads value from given index
    bool set(int index, int value);        // Sets value at given index
    void clear();                          // Clears whole array
};

#endif //PROJECT_ARRAY_H