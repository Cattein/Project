//
// Created by MariiaHuzhva on 22/03/2026.
//

#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H


#pragma once

//opis funkcji klasy(nazwa klasy, jakie zmienne, funkcje zawiera)

// dynamic array
class Array {
private:
    int* data;   // pointer to the array
    int size;    // number of array elements
public:
    Array(int size);  // constructor – creates arrays
    ~Array();      // destructor – frees memory
    // Czyli class Array potrafi tworzyc sie i usuwac

    int getSize() const { // Returns array size
        return size;
    };

    int& setId(int index){// Returns element at given index
    return data[index];
}
};

#endif //PROJECT_ARRAY_H