//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_QUICKSORT_H
#define PROJECT_QUICKSORT_H

#include "structures/Array.h"
#include "Parameters.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"


class QuickSort {
public:
    //static - metoda jest niezależna od obiektu
    //nie ma potrzeby tworzenia obiektu QuickSort
    //funkcja została po prostu umieszczona w klasie
    // *& - referencja na oryginalne tablice
    static void sort(Array<int>& array, Parameters::Pivots pivotType);
    static void sort(SingleList<int>& list, Parameters::Pivots pivotType);
    static void sort(DoubleList<int>& list, Parameters::Pivots pivotType);
};

#endif //PROJECT_QUICKSORT_H