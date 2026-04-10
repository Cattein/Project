//
// Created by MashaGuzhva on 10/04/2026.
//
#include "checking/SortingCheck.h"

bool SortingCheck::isSortedAscending(const Array& array) {
    for (int i = 1; i < array.getSize(); ++i) {
        int previous = 0;
        int current = 0;

        if (!array.get(i - 1, previous) || !array.get(i, current)) {
            return false;
        }

        if (current < previous) {
            return false;
        }
    }

    return true;
}