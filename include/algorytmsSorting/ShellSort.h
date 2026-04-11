//
// Created by MashaGuzhva on 11/04/2026.
//

#ifndef PROJECT_SHELLSORT_H
#define PROJECT_SHELLSORT_H
#include "structures/Array.h"

class ShellSort {
public:
    //static - metoda jest niezależna od obiektu
    //nie ma potrzeby tworzenia obiektu QuickSort
    //funkcja została po prostu umieszczona w klasie
    // Array& - referencja na oryginalne tablice
    static void sort(Array& array);
};



#endif //PROJECT_SHELLSORT_H