//
// Created by MashaGuzhva on 10/04/2026.
//

#include "algorytmsSorting/QuickSort.h"
#include <cstdlib>

// swap two numbers
static void swapValues(int& first, int& second) {
    // static - funkcja jest widoczna tylko w tym pliku
    // int& - referencję do oryginalnych danych - nie tworzy kopii

    const int temp = first;    // const - po utworzeniu tej zmiennej nie można już zmienić jej wartości
    // temp przechowuje 1 wartość, żeby nie została utracona podczas zamiany

    first = second;    // drugą wartość
    second = temp;     // wpisujemy zapamiętaną starą pierwszą wartość
}

// wybór indeksu pivota zależnie od parametru
static int choosePivotIndex(int left, int right, Parameters::Pivots pivotType) {
    if (pivotType == Parameters::Pivots::left) {
        return left;
    }

    if (pivotType == Parameters::Pivots::right) {
        return right;
    }

    if (pivotType == Parameters::Pivots::random) {
        return left + std::rand() % (right - left + 1);
    }

    // domyślnie pivot ze środka
    return (left + right) / 2;
}

// ===== array =====

static void QuickSorting(Array<int>& array, int left, int right, Parameters::Pivots pivotType) {
    // Array& - tablica jest przekazywana przez odwołanie

    int i, j, pivotIndex, pivot;

    pivotIndex = choosePivotIndex(left, right, pivotType);
    pivot = array.setId(pivotIndex);

    // przenosimy pivot na koniec
    swapValues(array.setId(pivotIndex), array.setId(right));

    j = left;  // indeks zew

    // przechodzimy po całym fragmencie != pivot
    for (i = left; i < right; i++) {

        // jeśli element jest mniejszy od pivota -> trafi do lewej części tablicy
        if (array.setId(i) < pivot) {
            swapValues(array.setId(i), array.setId(j));
            j++;
        }
    }

    // ustawiamy pivot na jego miejsce, gdzie po lewej stronie będą elementy < a po prawej >=
    swapValues(array.setId(right), array.setId(j));

    // jeśli po lewej stronie > 1 element - sortujemy
    if (left < j - 1) {
        QuickSorting(array, left, j - 1, pivotType);
    }

    // jeśli po prawej stronie > 1 element - sortujemy
    if (j + 1 < right) {
        QuickSorting(array, j + 1, right, pivotType);
    }
}

// ===== singlelist =====

static int getValue(const SingleList<int>& list, int index) {
    int value = 0;
    list.get(index, value);
    return value;
}

static void swapAt(SingleList<int>& list, int firstIndex, int secondIndex) {
    if (firstIndex == secondIndex) {
        return;
    }

    int firstValue = 0;
    int secondValue = 0;

    list.get(firstIndex, firstValue);
    list.get(secondIndex, secondValue);

    list.set(firstIndex, secondValue);
    list.set(secondIndex, firstValue);
}

static void QuickSorting(SingleList<int>& list, int left, int right, Parameters::Pivots pivotType) {
    int i, j, pivotIndex, pivot;

    pivotIndex = choosePivotIndex(left, right, pivotType);
    pivot = getValue(list, pivotIndex);

    // przenosimy pivot na koniec
    swapAt(list, pivotIndex, right);

    j = left;

    for (i = left; i < right; i++) {
        if (getValue(list, i) < pivot) {
            swapAt(list, i, j);
            j++;
        }
    }

    // ustawiamy pivot na jego miejsce
    swapAt(list, right, j);

    if (left < j - 1) {
        QuickSorting(list, left, j - 1, pivotType);
    }

    if (j + 1 < right) {
        QuickSorting(list, j + 1, right, pivotType);
    }
}

// ===== doublelist =====

static int getValue(const DoubleList<int>& list, int index) {
    int value = 0;
    list.get(index, value);
    return value;
}

static void swapAt(DoubleList<int>& list, int firstIndex, int secondIndex) {
    if (firstIndex == secondIndex) {
        return;
    }

    int firstValue = 0;
    int secondValue = 0;

    list.get(firstIndex, firstValue);
    list.get(secondIndex, secondValue);

    list.set(firstIndex, secondValue);
    list.set(secondIndex, firstValue);
}

static void QuickSorting(DoubleList<int>& list, int left, int right, Parameters::Pivots pivotType) {
    int i, j, pivotIndex, pivot;

    pivotIndex = choosePivotIndex(left, right, pivotType);
    pivot = getValue(list, pivotIndex);

    // przenosimy pivot na koniec
    swapAt(list, pivotIndex, right);

    j = left;

    for (i = left; i < right; i++) {
        if (getValue(list, i) < pivot) {
            swapAt(list, i, j);
            j++;
        }
    }

    // ustawiamy pivot na jego miejsce
    swapAt(list, right, j);

    if (left < j - 1) {
        QuickSorting(list, left, j - 1, pivotType);
    }

    if (j + 1 < right) {
        QuickSorting(list, j + 1, right, pivotType);
    }
}

// główna metoda klasy quicksort dla tablicy
void QuickSort::sort(Array<int>& array, Parameters::Pivots pivotType)
{
    // jeśli tablica ma 0 lub 1 element, to nic sortowac
    if (array.getSize() <= 1) {
        return;
    }

    // sortujemy tablicę od pierwszego do ostatniego indeksu
    QuickSorting(array, 0, array.getSize() - 1, pivotType);
}

// główna metoda klasy quicksort dla listy jednokierunkowej
void QuickSort::sort(SingleList<int>& list, Parameters::Pivots pivotType)
{
    if (list.getSize() <= 1) {
        return;
    }

    QuickSorting(list, 0, list.getSize() - 1, pivotType);
}

// główna metoda klasy quicksort dla listy dwukierunkowej
void QuickSort::sort(DoubleList<int>& list, Parameters::Pivots pivotType)
{
    if (list.getSize() <= 1) {
        return;
    }

    QuickSorting(list, 0, list.getSize() - 1, pivotType);
}