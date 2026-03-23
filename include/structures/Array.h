//
// Created by MariiaHuzhva on 22/03/2026.
//

#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H


#pragma once
//opis funkcji klasy(nazwa klasy, jakie zmienne, funkcje zawiera)

// dynamic array
struct Array {
private:
    int* data;   // pointer to the array
    int size;    // number of array elements
public:
    Array(int size);  // constructor – creates arrays
    ~Array();      // destructor – frees memory
};
// Czyli class Array ma rozmiar pointer do tablicy i potrafi tworzyc sie i usuwac

int getSize() const;
int& at(int index);

#endif //PROJECT_ARRAY_H