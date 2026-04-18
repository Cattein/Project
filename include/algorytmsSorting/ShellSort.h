//
// Created by MashaGuzhva on 11/04/2026.
//

#ifndef PROJECT_SHELLSORT_H
#define PROJECT_SHELLSORT_H

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "structures/Stack.h"
#include "Parameters.h"
#include "structures/BinaryTree.h"

class ShellSort {
private:
    // wspólny odczyt wartości spod danego indeksu
    template <typename Structure, typename T>
    static T readAt(const Structure& structure, int index) {
        T value{};
        // {} oznacza domyślną inicjalizację zmiennej
        // value chwilowo przechowuje odczytaną liczbę

        structure.get(index, value);
        // get wpisuje wartość spod danego indeksu do zmiennej value
        return value;
    }

    // wspólny zapis wartości pod danym indeksem
    template <typename Structure, typename T>
    static void writeAt(Structure& structure, int index, const T& value) {
        // Structure& - pracujemy na oryginalnej strukturze
        // const T& - wartość przekazujemy bez kopiowania
        // const - tej wartości nie zmieniamy w funkcji

        structure.set(index, value);
        // set podmienia wartość na wskazanej pozycji
    }

    // wspólna wersja insertion dla shellsorta
    template <typename Structure, typename T>
    static void insertion(Structure& structure, int gap) {
        // przechodzimy po strukturze od indeksu gap do końca
        for (int i = gap; i < structure.getSize(); ++i) {
            const T temp = readAt<Structure, T>(structure, i);
            // zapamiętujemy bieżący element, żeby nie zgubić go podczas przesuwania innych
            // const oznacza, że po utworzeniu temp nie zmieniamy jego wartości

            int j = i;
            // od tej pozycji zaczynamy szukać miejsca dla temp

            // dopóki element oddalony o gap jest większy od temp
            // przesuwamy go w prawo
            while (j >= gap && readAt<Structure, T>(structure, j - gap) > temp) {
                writeAt<Structure, T>(structure, j, readAt<Structure, T>(structure, j - gap));
                j -= gap;
            }

            writeAt<Structure, T>(structure, j, temp);
            // wstawiamy temp na właściwe miejsce
        }
    }

    template <typename Structure, typename T>
    static void shellHalfGaps(Structure& structure) {
        for (int gap = structure.getSize() / 2; gap > 0; gap /= 2) {
            insertion<Structure, T>(structure, gap);
        }
    }

    template <typename Structure, typename T>
    static void shellKnuthGaps(Structure& structure) {
        int gap = 1;

        // wyznaczamy największy odstęp knutha, który jeszcze pasuje do rozmiaru struktury
        while (gap < structure.getSize() / 3) {
            gap = 3 * gap + 1;
        }

        // sortujemy dla kolejnych coraz mniejszych odstępów
        while (gap >= 1) {
            insertion<Structure, T>(structure, gap);
            gap = (gap - 1) / 3;
        }
    }

    // wspólna funkcja uruchamiająca shellsort
    template <typename Structure, typename T>
    static void sortImpl(Structure& structure, Parameters::ShellParameters parameter) {
        // jeśli struktura ma 0 lub 1 element, nie trzeba nic sortować
        if (structure.getSize() <= 1) {
            return;
        }

        // option2 oznacza wariant z odstępami knutha
        if (parameter == Parameters::ShellParameters::option2) {
            shellKnuthGaps<Structure, T>(structure);
            return;
        }

        // w przeciwnym razie używamy prostszego dzielenia odstępu przez 2
        shellHalfGaps<Structure, T>(structure);
    }

public:
    template <typename T>
    static void sort(BinaryTree<T>& tree, Parameters::ShellParameters parameter) {
        sortImpl<BinaryTree<T>, T>(tree, parameter);
    }
    // uruchamia shellsort dla tablicy
    template <typename T>
    static void sort(Array<T>& array, Parameters::ShellParameters parameter) {
        sortImpl<Array<T>, T>(array, parameter);
    }

    // uruchamia shellsort dla listy jednokierunkowej
    template <typename T>
    static void sort(SingleList<T>& list, Parameters::ShellParameters parameter) {
        sortImpl<SingleList<T>, T>(list, parameter);
    }

    // uruchamia shellsort dla listy dwukierunkowej
    template <typename T>
    static void sort(DoubleList<T>& list, Parameters::ShellParameters parameter) {
        sortImpl<DoubleList<T>, T>(list, parameter);
    }

    // uruchamia shellsort dla stosu
    template <typename T>
    static void sort(Stack<T>& stack, Parameters::ShellParameters parameter) {
        sortImpl<Stack<T>, T>(stack, parameter);
    }
};

#endif // PROJECT_SHELLSORT_H