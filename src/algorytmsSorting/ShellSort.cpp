#include "algorytmsSorting/ShellSort.h"

namespace { //  widoczne tylko w tym pliku

    // odczytuje wartość spod danego indeksu w tablicy
    int readAt(const Array<int>& array, int index) {
        // const Array& - tablica  przekazywana bez kopiowania
        // const - tej tablicy nie można tutaj zmieniać
        return array.setId(index);
    }

    // zapisuje wartość pod danym indeksem w tablicy
    void writeAt(Array<int>& array, int index, int value) {
        // Array& - pracujemy na oryginalnej tablicy
        array.setId(index) = value;
    }
    
    // odczytuje wartość spod danego indeksu w liście jednokierunkowej
    int readAt(const SingleList<int>& list, int index) {
        int value = 0;    // value chwilowo przechowuje odczytaną liczbę
        list.get(index, value);// get wpisuje wartość spod danego indeksu do zmiennej value
        return value;
    }

    // zapisuje wartość pod danym indeksem w liście jednokierunkowej
    void writeAt(SingleList<int>& list, int index, int value) {
        list.set(index, value);    // set podmienia wartość na wskazanej pozycji

    }
    
    // odczytuje wartość spod danego indeksu w liście dwukierunkowej
    int readAt(const DoubleList<int>& list, int index) {
        int value = 0;    // value chwilowo przechowuje odczytaną liczbę

        list.get(index, value);    // get wpisuje wartość spod danego indeksu do zmiennej value
        return value;
    }

    // zapisuje wartość pod danym indeksem w liście dwukierunkowej
    void writeAt(DoubleList<int>& list, int index, int value) {
        list.set(index, value);    // set podmienia wartość na wskazanej pozycji

    }


    // template napisać jedną funkcję dla różnych struktur
    // Structure będzie tutaj zastąpione prawdziwym typem
    template <typename Structure>
    void insertion(Structure& structure, int gap) {
        // przechodzimy po strukturze od indeksu gap do końca
        for (int i = gap; i < structure.getSize(); ++i) {
            const int temp = readAt(structure, i);
            // zapamiętujemy bieżący element, żeby nie zgubić go podczas przesuwania innych

            int j = i;// od tej pozycji zaczynamy szukać miejsca dla temp

            // dopóki element oddalony o gap  większy od temp
            // przesuwamy go w prawo
            while (j >= gap && readAt(structure, j - gap) > temp) {
                writeAt(structure, j, readAt(structure, j - gap));
                j -= gap;
            }

            writeAt(structure, j, temp);// wstawiamy temp na właściwe miejsce
        }
    }

    // 1 wariant shella
    // odstęp zmniejszamy przez 2
    template <typename Structure>
    void shellHalfGaps(Structure& structure) {
        for (int gap = structure.getSize() / 2; gap > 0; gap /= 2) {
            insertion(structure, gap);
        }
    }

    // 2 wariant shella
    // używamy odstępów knutha
    template <typename Structure>
    void shellKnuthGaps(Structure& structure) {
        int gap = 1;

        // wyznaczamy największy odstęp knutha, który jeszcze pasuje do rozmiaru struktury
        while (gap < structure.getSize() / 3) {
            gap = 3 * gap + 1;
        }

        // sortujemy dla kolejnych coraz mniejszych odstępów
        while (gap >= 1) {
            insertion(structure, gap);
            gap = (gap - 1) / 3;
        }
    }

    // wspólna funkcja wybierająca wariant shellsorta
    template <typename Structure>
    void shellSortImpl(Structure& structure, Parameters::ShellParameters parameter) {
        // jeśli struktura ma 0 lub 1 element, nie trzeba nic sortować
        if (structure.getSize() <= 1) {
            return;
        }

        // option2 oznacza wariant z odstępami knutha
        if (parameter == Parameters::ShellParameters::option2) {
            shellKnuthGaps(structure);
            return;
        }

        // w przeciwnym razie używamy prostszego dzielenia odstępu przez 2
        shellHalfGaps(structure);
    }

}

// uruchamia shellsort dla tablicy
void ShellSort::sort(Array<int>& array, Parameters::ShellParameters parameter) {
    shellSortImpl(array, parameter);
}

// uruchamia shellsort dla listy jednokierunkowej
void ShellSort::sort(SingleList<int>& list, Parameters::ShellParameters parameter) {
    shellSortImpl(list, parameter);
}

// uruchamia shellsort dla listy dwukierunkowej
void ShellSort::sort(DoubleList<int>& list, Parameters::ShellParameters parameter) {
    shellSortImpl(list, parameter);
}