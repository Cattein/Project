//
// Created by MariiaHuzhva on 22/03/2026.
//

#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H


#pragma once
//opis funkcji klasy(nazwa klasy, jakie zmienne, funkcje zawiera)

// dynamic array
struct Array {
    int* data;   // pointer to the array
    int size;    // number of array elements

    Array(int size);  // constructor – creates arrays
    ~Array();      // destructor – frees memory
};
// Czyli class Array ma rozmiar pointer do tablicy i potrafi tworzyc sie i usuwac(aby nie bylo

#endif //PROJECT_ARRAY_H