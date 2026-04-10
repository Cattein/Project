//
// Created by MashaGuzhva on 10/04/2026.
//

#include "../../include/algorytmsSorting/QuickSort.h"

namespace {
    void swapValues(int& first, int& second) {
        const int temp = first;
        first = second;
        second = temp;
    }

    int partition(Array& array, int left, int right) {
        const int pivot = array.setId(right);
        int i = left - 1;

        for (int j = left; j < right; ++j) {
            if (array.setId(j) <= pivot) {
                ++i;
                swapValues(array.setId(i), array.setId(j));
            }
        }

        swapValues(array.setId(i + 1), array.setId(right));
        return i + 1;
    }

    void quickSortRecursive(Array& array, int left, int right) {
        if (left >= right) {
            return;
        }

        const int pivotIndex = partition(array, left, right);

        quickSortRecursive(array, left, pivotIndex - 1);
        quickSortRecursive(array, pivotIndex + 1, right);
    }
}

void QuickSort::sort(Array& array) {
    if (array.getSize() <= 1) {
        return;
    }

    quickSortRecursive(array, 0, array.getSize() - 1);
}