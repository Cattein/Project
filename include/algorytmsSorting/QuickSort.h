//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_QUICKSORT_H
#define PROJECT_QUICKSORT_H

#include <cstdlib>

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "structures/Stack.h"
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

    // wspólny odczyt wartości dla każdej struktury
    template <typename Structure, typename T>
    static T getValue(const Structure& structure, int index) {
        T value{};
        // {} oznacza domyślną inicjalizację zmiennej

        structure.get(index, value);
        return value;
    }

    // wspólna zamiana elementów miejscami dla każdej struktury
    template <typename Structure, typename T>
    static void swapAt(Structure& structure, int firstIndex, int secondIndex) {
        if (firstIndex == secondIndex) {
            return;
        }

        T firstValue{};
        T secondValue{};

        structure.get(firstIndex, firstValue);
        structure.get(secondIndex, secondValue);

        structure.set(firstIndex, secondValue);
        structure.set(secondIndex, firstValue);
    }

    // wspólna implementacja quicksorta
    template <typename Structure, typename T>
    static void QuickSorting(Structure& structure, int left, int right, Parameters::Pivots pivotType) {
        // Structure& - struktura jest przekazywana przez odwołanie
        // template <typename Structure, typename T> oznacza,
        // że sortowanie działa dla różnych struktur i różnych typów danych

        if (left >= right) {
            return;
        }
        // jeśli zakres ma 0 lub 1 element, to nic sortowac

        int i, j, pivotIndex;
        T pivot;
        // T pivot - pivot ma ten sam typ co elementy struktury

        pivotIndex = choosePivotIndex(left, right, pivotType);
        pivot = getValue<Structure, T>(structure, pivotIndex);

        // przenosimy pivot na koniec
        swapAt<Structure, T>(structure, pivotIndex, right);

        j = left;

        // przechodzimy po całym fragmencie != pivot
        for (i = left; i < right; i++) {

            // jeśli element jest mniejszy od pivota -> trafi do lewej części
            if (getValue<Structure, T>(structure, i) < pivot) {
                swapAt<Structure, T>(structure, i, j);
                j++;
            }
        }

        // ustawiamy pivot na jego miejsce, gdzie po lewej stronie będą elementy < a po prawej >=
        swapAt<Structure, T>(structure, right, j);

        // jeśli po lewej stronie > 1 element - sortujemy
        if (left < j - 1) {
            QuickSorting<Structure, T>(structure, left, j - 1, pivotType);
        }

        // jeśli po prawej stronie > 1 element - sortujemy
        if (j + 1 < right) {
            QuickSorting<Structure, T>(structure, j + 1, right, pivotType);
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
        QuickSorting<Array<T>, T>(array, 0, array.getSize() - 1, pivotType);
    }

    // główna metoda klasy quicksort dla listy jednokierunkowej
    template <typename T>
    static void sort(SingleList<T>& list, Parameters::Pivots pivotType)
    {
        if (list.getSize() <= 1) {
            return;
        }

        QuickSorting<SingleList<T>, T>(list, 0, list.getSize() - 1, pivotType);
    }

    // główna metoda klasy quicksort dla listy dwukierunkowej
    template <typename T>
    static void sort(DoubleList<T>& list, Parameters::Pivots pivotType)
    {
        if (list.getSize() <= 1) {
            return;
        }

        QuickSorting<DoubleList<T>, T>(list, 0, list.getSize() - 1, pivotType);
    }

    // główna metoda klasy quicksort dla stosu
    template <typename T>
    static void sort(Stack<T>& stack, Parameters::Pivots pivotType)
    {
        if (stack.getSize() <= 1) {
            return;
        }

        QuickSorting<Stack<T>, T>(stack, 0, stack.getSize() - 1, pivotType);
    }
};

#endif // PROJECT_QUICKSORT_H