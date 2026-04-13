//
// Created by MashaGuzhva on 11/04/2026.
//

#ifndef PROJECT_BUCKETSORT_H
#define PROJECT_BUCKETSORT_H
#include "structures/Array.h"
#include "structures/DoubleList.h"
#include "structures/SingleList.h"


class BucketSort {
public:
    // static metody - nie wywołujemy na obiekcie klasy
    static bool sort(Array<int>& array);
    // Array<int>& - tablica jest przekazywana przez referencję
    // sortowanie działa na oryginalnych danych, a nie na kopii

    static bool sort(SingleList<int>& array);
    // SingleList<int>& - lista jednokierunkowa jest przekazywana przez referencję
    // funkcja sortuje prawdziwą listę, a nie jej kopię

    static bool sort(DoubleList<int>& array);
    // DoubleList<int>& - lista dwukierunkowa jest przekazywana przez referencję
    // funkcja działa bezpośrednio na oryginalnej strukturze
};

#endif //PROJECT_BUCKETSORT_H