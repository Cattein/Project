//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_SORTINGCHECK_H
#define PROJECT_SORTINGCHECK_H
#include "structures/Array.h"
#include "structures/DoubleList.h"
#include "structures/SingleList.h"

class SortingCheck {
public:
     //static - metoda jest niezależna od obiektu
     //nie ma potrzeby tworzenia obiektu QuickSort
     //funkcja została po prostu umieszczona w klasie
     // bool - funkcja zwraca true albo false
     // Array& - referencja na oryginalne tablice
     static bool SortedAscend(const Array& array);
     static bool SortedAscend(const DoubleList& list);
     static bool SortedAscend(const SingleList& list);

};


#endif //PROJECT_SORTINGCHECK_H