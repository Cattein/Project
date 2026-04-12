//
// Created by MashaGuzhva on 12/04/2026.
//

#include "benchmark/RandomArrayGenerator.h"

#include <new>
#include <cstdlib>
#include <ctime>

// wypełnia tablicę losowymi liczbami
bool RandomArrayGenerator::fillRandom(Array& array) {
    // static sprawia, że ta zmienna nie tworzy się od nowa przy każdym wywołaniu
    static bool seeded = false;    // seeded zapamiętuje, czy generator został już ustawiony


    // jeśli generator jeszcze nie był ustawiony, ustawiamy go aktualnym czasem
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    // przechodzimy po całej tablicy i wpisujemy do niej liczby losowe
    for (int i = 0; i < array.getSize(); ++i) {

        if (!array.set(i, std::rand())) {
            return false;    // jeśli nie uda się zapisać wartości do tablicy, zwracamy false

        }
    }
    return true;
}

// tworzy kopię podanej tablicy
Array* RandomArrayGenerator::copyArray(const Array& source) {
    // tworzymy nową tablicę o takim samym rozmiarze jak source
    Array* copy = new (std::nothrow) Array(source.getSize());
    // std::nothrow - przy braku pamięci dostaniemy nullptr

    // jeśli nie udało się utworzyć nowej tablicy, zwracamy nullptr
    if (copy == nullptr) {
        return nullptr;
    }

    // przepisujemy elementy z tablicy source do nowej tablicy
    for (int i = 0; i < source.getSize(); ++i) {
        int value = 0;   // value przechowuje odczytaną liczbę


        // odczytujemy element z oryginalnej tablicy
        if (!source.get(i, value)) {
            delete copy;
            return nullptr;
        }

        // zapisujemy odczytaną wartość do nowej tablicy
        if (!copy->set(i, value)) {
            delete copy;
            return nullptr;
        }
    }

    // zwracamy gotową kopię tablicy
    return copy;
}