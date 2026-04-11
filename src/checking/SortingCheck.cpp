//
// Created by MashaGuzhva on 10/04/2026.
//
#include "checking/SortingCheck.h"

bool SortingCheck::SortedAscend(const Array& array) {
    // przechodzimy po tablicy od drugiego elementu
    for (int i = 1; i < array.getSize(); ++i) {
        int last = 0;        // poprzedni element
        int current = 0;     // aktualny element

        // jeśli odczyt się nie uda, zwracamy false
        if (!array.get(i - 1, last) || !array.get(i, current)) {
            return false;
        }

        // jeśli aktualny element jest mniejszy od poprzedniego - tablica nie jest posortowana rosnąco
        if (current < last) {
            return false;
        }
    }
    return true;
}