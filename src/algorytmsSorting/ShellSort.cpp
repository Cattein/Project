//
// Created by MashaGuzhva on 11/04/2026.
//
#include "algorytmsSorting/ShellSort.h"


static void insertionWithGap(Array& array, int gap) {
    for (int i = gap; i < array.getSize(); ++i) {
        const int temp = array.setId(i);
        int j = i;

        while (j >= gap && array.setId(j - gap) > temp) {
            array.setId(j) = array.setId(j - gap);
            j -= gap;
        }

        array.setId(j) = temp;
    }
}

static void shellHalfGaps(Array& array) {
    for (int gap = array.getSize() / 2; gap > 0; gap /= 2) {
        insertionWithGap(array, gap);
    }
}


void ShellSort::sort(Array& array, Parameters::ShellParameters parameter) {
    if (array.getSize() <= 1) {
        return;
    }

    if (parameter == Parameters::ShellParameters::option2) {
        return;
    }

    shellHalfGaps(array);

    // sortujemy tablicę od pierwszego do ostatniego indeksu
}


