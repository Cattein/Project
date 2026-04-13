//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_QUICKSORT_H
#define PROJECT_QUICKSORT_H

#include <cstdlib>

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "Parameters.h"

class QuickSort {
private:
    // swap two numbers
    template <typename T>
    static void swapValues(T& first, T& second) {
        // T& - referencję do oryginalnych danych - nie tworzy kopii
        // template <typename T> oznacza, że funkcja działa dla różnych typów danych

        const T temp = first;
        // const - po utworzeniu tej zmiennej nie można już zmienić jej wartości
        // temp przechowuje 1 wartość, żeby nie została utracona podczas zamiany

        first = second;
        second = temp;
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

    template <typename T>
    static void QuickSorting(Array<T>& array, int left, int right, Parameters::Pivots pivotType) {
        // Array<T>& - tablica jest przekazywana przez odwołanie
        // template <typename T> oznacza, że sortowanie działa dla różnych typów danych

        if (left >= right) {
            return;
        }
        // jeśli zakres ma 0 lub 1 element, to nic sortowac

        int i, j, pivotIndex;
        T pivot;
        // T pivot - pivot ma ten sam typ co elementy tablicy

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

    template <typename T>
    static T getValue(const SingleList<T>& list, int index) {
        T value{};
        // {} oznacza domyślną inicjalizację zmiennej

        list.get(index, value);
        return value;
    }

    template <typename T>
    static void swapAt(SingleList<T>& list, int firstIndex, int secondIndex) {
        if (firstIndex == secondIndex) {
            return;
        }

        T firstValue{};
        T secondValue{};

        list.get(firstIndex, firstValue);
        list.get(secondIndex, secondValue);

        list.set(firstIndex, secondValue);
        list.set(secondIndex, firstValue);
    }

    template <typename T>
    static void QuickSorting(SingleList<T>& list, int left, int right, Parameters::Pivots pivotType) {
        if (left >= right) {
            return;
        }

        int i, j, pivotIndex;
        T pivot;

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

    template <typename T>
    static T getValue(const DoubleList<T>& list, int index) {
        T value{};
        list.get(index, value);
        return value;
    }

    template <typename T>
    static void swapAt(DoubleList<T>& list, int firstIndex, int secondIndex) {
        if (firstIndex == secondIndex) {
            return;
        }

        T firstValue{};
        T secondValue{};

        list.get(firstIndex, firstValue);
        list.get(secondIndex, secondValue);

        list.set(firstIndex, secondValue);
        list.set(secondIndex, firstValue);
    }

    template <typename T>
    static void QuickSorting(DoubleList<T>& list, int left, int right, Parameters::Pivots pivotType) {
        if (left >= right) {
            return;
        }

        int i, j, pivotIndex;
        T pivot;

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

public:
    // główna metoda klasy quicksort dla tablicy
    template <typename T>
    static void sort(Array<T>& array, Parameters::Pivots pivotType)
    {
        // jeśli tablica ma 0 lub 1 element, to nic sortowac
        if (array.getSize() <= 1) {
            return;
        }

        // sortujemy tablicę od pierwszego do ostatniego indeksu
        QuickSorting(array, 0, array.getSize() - 1, pivotType);
    }

    // główna metoda klasy quicksort dla listy jednokierunkowej
    template <typename T>
    static void sort(SingleList<T>& list, Parameters::Pivots pivotType)
    {
        if (list.getSize() <= 1) {
            return;
        }

        QuickSorting(list, 0, list.getSize() - 1, pivotType);
    }

    // główna metoda klasy quicksort dla listy dwukierunkowej
    template <typename T>
    static void sort(DoubleList<T>& list, Parameters::Pivots pivotType)
    {
        if (list.getSize() <= 1) {
            return;
        }

        QuickSorting(list, 0, list.getSize() - 1, pivotType);
    }
};

#endif // PROJECT_QUICKSORT_H