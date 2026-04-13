//
// Created by MashaGuzhva on 11/04/2026.
//

#ifndef PROJECT_SHELLSORT_H
#define PROJECT_SHELLSORT_H

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "Parameters.h"

class ShellSort {
private:
    // ===== odczyt wartości =====

    // odczytuje wartość spod danego indeksu w tablicy
    template <typename T>
    static T readAt(const Array<T>& array, int index) {
        // const Array<T>& - tablica jest przekazywana bez kopiowania
        // const - tej tablicy nie można tutaj zmieniać
        return array.setId(index);
    }

    // odczytuje wartość spod danego indeksu w liście jednokierunkowej
    template <typename T>
    static T readAt(const SingleList<T>& list, int index) {
        T value{};
        // {} oznacza domyślną inicjalizację zmiennej
        // value chwilowo przechowuje odczytaną liczbę

        list.get(index, value);
        // get wpisuje wartość spod danego indeksu do zmiennej value
        return value;
    }

    // odczytuje wartość spod danego indeksu w liście dwukierunkowej
    template <typename T>
    static T readAt(const DoubleList<T>& list, int index) {
        T value{};
        // value chwilowo przechowuje odczytaną liczbę

        list.get(index, value);
        // get wpisuje wartość spod danego indeksu do zmiennej value
        return value;
    }

    // ===== zapis wartości =====

    // zapisuje wartość pod danym indeksem w tablicy
    template <typename T>
    static void writeAt(Array<T>& array, int index, const T& value) {
        // Array<T>& - pracujemy na oryginalnej tablicy
        // const T& - wartość przekazujemy bez kopiowania
        // const - tej wartości nie zmieniamy w funkcji

        array.setId(index) = value;
    }

    // zapisuje wartość pod danym indeksem w liście jednokierunkowej
    template <typename T>
    static void writeAt(SingleList<T>& list, int index, const T& value) {
        list.set(index, value);
        // set podmienia wartość na wskazanej pozycji
    }

    // zapisuje wartość pod danym indeksem w liście dwukierunkowej
    template <typename T>
    static void writeAt(DoubleList<T>& list, int index, const T& value) {
        list.set(index, value);
        // set podmienia wartość na wskazanej pozycji
    }

    // ===== array =====

    template <typename T>
    static void insertion(Array<T>& array, int gap) {
        // przechodzimy po strukturze od indeksu gap do końca
        for (int i = gap; i < array.getSize(); ++i) {
            const T temp = readAt(array, i);
            // zapamiętujemy bieżący element, żeby nie zgubić go podczas przesuwania innych
            // const oznacza, że po utworzeniu temp nie zmieniamy jego wartości

            int j = i;
            // od tej pozycji zaczynamy szukać miejsca dla temp

            // dopóki element oddalony o gap jest większy od temp
            // przesuwamy go w prawo
            while (j >= gap && readAt(array, j - gap) > temp) {
                writeAt(array, j, readAt(array, j - gap));
                j -= gap;
            }

            writeAt(array, j, temp);
            // wstawiamy temp na właściwe miejsce
        }
    }

    template <typename T>
    static void shellHalfGaps(Array<T>& array) {
        for (int gap = array.getSize() / 2; gap > 0; gap /= 2) {
            insertion(array, gap);
        }
    }

    template <typename T>
    static void shellKnuthGaps(Array<T>& array) {
        int gap = 1;

        // wyznaczamy największy odstęp knutha, który jeszcze pasuje do rozmiaru struktury
        while (gap < array.getSize() / 3) {
            gap = 3 * gap + 1;
        }

        // sortujemy dla kolejnych coraz mniejszych odstępów
        while (gap >= 1) {
            insertion(array, gap);
            gap = (gap - 1) / 3;
        }
    }

    // ===== single list =====

    template <typename T>
    static void insertion(SingleList<T>& list, int gap) {
        // przechodzimy po strukturze od indeksu gap do końca
        for (int i = gap; i < list.getSize(); ++i) {
            const T temp = readAt(list, i);
            // zapamiętujemy bieżący element, żeby nie zgubić go podczas przesuwania innych
            // const oznacza, że po utworzeniu temp nie zmieniamy jego wartości

            int j = i;
            // od tej pozycji zaczynamy szukać miejsca dla temp

            // dopóki element oddalony o gap jest większy od temp
            // przesuwamy go w prawo
            while (j >= gap && readAt(list, j - gap) > temp) {
                writeAt(list, j, readAt(list, j - gap));
                j -= gap;
            }

            writeAt(list, j, temp);
            // wstawiamy temp na właściwe miejsce
        }
    }

    template <typename T>
    static void shellHalfGaps(SingleList<T>& list) {
        for (int gap = list.getSize() / 2; gap > 0; gap /= 2) {
            insertion(list, gap);
        }
    }

    template <typename T>
    static void shellKnuthGaps(SingleList<T>& list) {
        int gap = 1;

        // wyznaczamy największy odstęp knutha, który jeszcze pasuje do rozmiaru struktury
        while (gap < list.getSize() / 3) {
            gap = 3 * gap + 1;
        }

        // sortujemy dla kolejnych coraz mniejszych odstępów
        while (gap >= 1) {
            insertion(list, gap);
            gap = (gap - 1) / 3;
        }
    }

    // ===== double list =====

    template <typename T>
    static void insertion(DoubleList<T>& list, int gap) {
        // przechodzimy po strukturze od indeksu gap do końca
        for (int i = gap; i < list.getSize(); ++i) {
            const T temp = readAt(list, i);
            // zapamiętujemy bieżący element, żeby nie zgubić go podczas przesuwania innych
            // const oznacza, że po utworzeniu temp nie zmieniamy jego wartości

            int j = i;
            // od tej pozycji zaczynamy szukać miejsca dla temp

            // dopóki element oddalony o gap jest większy od temp
            // przesuwamy go w prawo
            while (j >= gap && readAt(list, j - gap) > temp) {
                writeAt(list, j, readAt(list, j - gap));
                j -= gap;
            }

            writeAt(list, j, temp);
            // wstawiamy temp na właściwe miejsce
        }
    }

    template <typename T>
    static void shellHalfGaps(DoubleList<T>& list) {
        for (int gap = list.getSize() / 2; gap > 0; gap /= 2) {
            insertion(list, gap);
        }
    }

    template <typename T>
    static void shellKnuthGaps(DoubleList<T>& list) {
        int gap = 1;

        // wyznaczamy największy odstęp knutha, który jeszcze pasuje do rozmiaru struktury
        while (gap < list.getSize() / 3) {
            gap = 3 * gap + 1;
        }

        // sortujemy dla kolejnych coraz mniejszych odstępów
        while (gap >= 1) {
            insertion(list, gap);
            gap = (gap - 1) / 3;
        }
    }

public:
    // uruchamia shellsort dla tablicy
    template <typename T>
    static void sort(Array<T>& array, Parameters::ShellParameters parameter) {
        // jeśli struktura ma 0 lub 1 element, nie trzeba nic sortować
        if (array.getSize() <= 1) {
            return;
        }

        // option2 oznacza wariant z odstępami knutha
        if (parameter == Parameters::ShellParameters::option2) {
            shellKnuthGaps(array);
            return;
        }

        // w przeciwnym razie używamy prostszego dzielenia odstępu przez 2
        shellHalfGaps(array);
    }

    // uruchamia shellsort dla listy jednokierunkowej
    template <typename T>
    static void sort(SingleList<T>& list, Parameters::ShellParameters parameter) {
        // jeśli struktura ma 0 lub 1 element, nie trzeba nic sortować
        if (list.getSize() <= 1) {
            return;
        }

        // option2 oznacza wariant z odstępami knutha
        if (parameter == Parameters::ShellParameters::option2) {
            shellKnuthGaps(list);
            return;
        }

        // w przeciwnym razie używamy prostszego dzielenia odstępu przez 2
        shellHalfGaps(list);
    }

    // uruchamia shellsort dla listy dwukierunkowej
    template <typename T>
    static void sort(DoubleList<T>& list, Parameters::ShellParameters parameter) {
        // jeśli struktura ma 0 lub 1 element, nie trzeba nic sortować
        if (list.getSize() <= 1) {
            return;
        }

        // option2 oznacza wariant z odstępami knutha
        if (parameter == Parameters::ShellParameters::option2) {
            shellKnuthGaps(list);
            return;
        }

        // w przeciwnym razie używamy prostszego dzielenia odstępu przez 2
        shellHalfGaps(list);
    }
};

#endif // PROJECT_SHELLSORT_H