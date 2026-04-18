//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_QUICKSORT_H
#define PROJECT_QUICKSORT_H

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "structures/Stack.h"
#include "Parameters.h"
#include "structures/BinaryTree.h"

class QuickSort {
private:

    // wybiera indeks pivota zależnie od parametru podanego przez użytkownika
    static int choosePivotIndex(int left, int right, Parameters::Pivots pivotType) {
        // pivot to pierwszy element zakresu
        if (pivotType == Parameters::Pivots::left) {
            return left;
        }

        // pivot to ostatni element zakresu
        if (pivotType == Parameters::Pivots::right) {
            return right;
        }

        // pivot losowy z zakresu <left, right>
        if (pivotType == Parameters::Pivots::random) {
            return left + std::rand() % (right - left + 1);
        }

        // domyślnie pivot ze środka
        return (left + right) / 2;
    }

    // wspólny odczyt wartości spod danego indeksu
    // działa dla każdej struktury, która ma metodę get(index, value)
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
        // jeśli indeksy są takie same, nie ma czego zamieniać
        if (firstIndex == secondIndex) {
            return;
        }

        T firstValue{};
        T secondValue{};
        // zmienne pomocnicze do przechowania odczytanych wartości

        structure.get(firstIndex, firstValue);
        structure.get(secondIndex, secondValue);

        structure.set(firstIndex, secondValue);
        structure.set(secondIndex, firstValue);
    }

    // wspólna implementacja quicksorta
    template <typename Structure, typename T>
    static void QuickSorting(Structure& structure, int left, int right, Parameters::Pivots pivotType) {
        // Structure& - struktura jest przekazywana przez referencję
        // więc sortowanie działa bezpośrednio na oryginalnych danych

        // jeśli zakres ma 0 lub 1 element, nic nie trzeba sortować
        if (left >= right) {
            return;
        }

        T pivot;
        // pivot ma ten sam typ co elementy struktury

        // wybieramy indeks pivota i odczytujemy jego wartość
        int pivotIndex = choosePivotIndex(left, right, pivotType);
        pivot = getValue<Structure, T>(structure, pivotIndex);

        // przenosimy pivot na koniec badanego zakresu
        swapAt<Structure, T>(structure, pivotIndex, right);

        // j będzie wskazywać miejsce,
        // gdzie powinien trafić kolejny element mniejszy od pivota
        int j = left;

        // przechodzimy po wszystkich elementach oprócz pivota,
        // który chwilowo stoi na końcu
        for (int i = left; i < right; i++) {
            // jeśli element jest mniejszy od pivota,
            // przenosimy go do lewej części
            if (getValue<Structure, T>(structure, i) < pivot) {
                swapAt<Structure, T>(structure, i, j);
                j++;
            }
        }

        // ustawiamy pivot na jego ostatecznym miejscu
        // po lewej stronie będą elementy < pivot,
        // po prawej stronie elementy >= pivot
        swapAt<Structure, T>(structure, right, j);

        // sortujemy lewą część
        if (left < j - 1) {
            QuickSorting<Structure, T>(structure, left, j - 1, pivotType);
        }

        // sortujemy prawą część
        if (j + 1 < right) {
            QuickSorting<Structure, T>(structure, j + 1, right, pivotType);
        }
    }

public:
    // uruchamia quicksort dla drzewa binarnego
    template <typename T>
    static void sort(BinaryTree<T>& tree, Parameters::Pivots pivotType)
    {
        // jeśli drzewo ma 0 lub 1 element, jest już posortowane
        if (tree.getSize() <= 1) {
            return;
        }

        QuickSorting<BinaryTree<T>, T>(tree, 0, tree.getSize() - 1, pivotType);
        // drzewo traktujemy jak strukturę indeksowaną poziomami
    }

    // uruchamia quicksort dla tablicy
    template <typename T>
    static void sort(Array<T>& array, Parameters::Pivots pivotType)
    {
        // jeśli tablica ma 0 lub 1 element, nic nie sortujemy
        if (array.getSize() <= 1) {
            return;
        }

        // sortujemy cały zakres tablicy
        QuickSorting<Array<T>, T>(array, 0, array.getSize() - 1, pivotType);
    }

    // uruchamia quicksort dla listy jednokierunkowej
    template <typename T>
    static void sort(SingleList<T>& list, Parameters::Pivots pivotType)
    {
        // lista pusta albo jednoelementowa jest już posortowana
        if (list.getSize() <= 1) {
            return;
        }

        QuickSorting<SingleList<T>, T>(list, 0, list.getSize() - 1, pivotType);
    }

    // uruchamia quicksort dla listy dwukierunkowej
    template <typename T>
    static void sort(DoubleList<T>& list, Parameters::Pivots pivotType)
    {
        // lista pusta albo jednoelementowa nie wymaga sortowania
        if (list.getSize() <= 1) {
            return;
        }

        QuickSorting<DoubleList<T>, T>(list, 0, list.getSize() - 1, pivotType);
    }

    // uruchamia quicksort dla stosu
    template <typename T>
    static void sort(Stack<T>& stack, Parameters::Pivots pivotType)
    {
        // jeśli stos ma 0 lub 1 element, nic nie trzeba robić
        if (stack.getSize() <= 1) {
            return;
        }

        QuickSorting<Stack<T>, T>(stack, 0, stack.getSize() - 1, pivotType);
    }
};

#endif // PROJECT_QUICKSORT_H