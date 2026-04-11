//
// Created by MashaGuzhva on 11/04/2026.
//

#include "algorytmsSorting/ShellSort.h"

// static - funkcja widoczna tylko w tym pliku
static void insertion(Array& array, int gap) {

    // zaczynamy od elementu o indeksie gap
    for (int i = gap; i < array.getSize(); ++i) {
        const int temp = array.setId(i);    // zapamiętujemy wartość bieżącego elementu
        int j = i;   // od tej pozycji zaczynamy szukać miejsca, gdzie trzeba wstawić temp

        // porównujemy elementy oddalone o gap
        while (j >= gap && array.setId(j - gap) > temp) {
            array.setId(j) = array.setId(j - gap);    // jeśli wcześniejszy element jest większy, przesuwamy go w prawo
            j -= gap;
        }
        // wstawiamy zapamiętaną wartość tam, gdzie już pasuje
        array.setId(j) = temp;
    }
}

//zmniejsza odstęp o połowę
static void shellHalfGaps(Array& array) {
    for (int gap = array.getSize() / 2; gap > 0; gap /= 2) {
        insertion(array, gap);
    }
}

// wzor 3 * gap + 1
static void shellKnuthGaps(Array& array) {
    int gap = 1;

    // szukamy największego odstępu knutha, który jeszcze mieści się w tablicy
    while (gap < array.getSize() / 3) {
        gap = 3 * gap + 1;
    }

    // sortujemy dla kolejnych mniejszych odstępów
    // na końcu gap będzie równe 1 -> działa jak zwykły insertion sort
    while (gap >= 1) {
        insertion(array, gap);
        gap = (gap - 1) / 3;
    }
}

// główna metoda klasy shellsort
void ShellSort::sort(Array& array, Parameters::ShellParameters parameter) {
    if (array.getSize() <= 1) { // jeśli tablica ma 0 lub 1 element, nie trzeba nic robić
        return;
    }

    // option2 oznacza, że wybieramy wariant z odstępami knutha
    if (parameter == Parameters::ShellParameters::option2) {
        shellKnuthGaps(array);
        return;
    }

    shellHalfGaps(array);    // w przeciwnym razie używamy prostszego dzielenia odstępu przez 2

}