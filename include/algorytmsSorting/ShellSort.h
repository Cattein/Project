//
// Created by MashaGuzhva on 11/04/2026.
//

#ifndef PROJECT_SHELLSORT_H
#define PROJECT_SHELLSORT_H
#include "structures/Array.h"
#include "Parameters.h"
#include "structures/DoubleList.h"
#include "structures/SingleList.h"

class ShellSort {
public:
    //static - metoda jest niezależna od obiektu,
    //nie ma potrzeby tworzenia obiektu,
    //funkcja została po prostu umieszczona w klasie
    // Array& - referencja na oryginalne tablice
    static void sort(Array<int>& array,  Parameters::ShellParameters parameter);
    static void sort(SingleList<int>& list,  Parameters::ShellParameters parameter);
    static void sort(DoubleList<int>& list,  Parameters::ShellParameters parameter);



};



#endif //PROJECT_SHELLSORT_H