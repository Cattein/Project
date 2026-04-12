#include "benchmark/RandomArrayGenerator.h"

#include <new>
#include <cstdlib>

// stały seed
static void seedRandomOnce() {
    // static sprawia, że generator ustawiamy tylko raz
    static bool seeded = false;

    if (!seeded) {
        std::srand(12345);
        // srand ustawia punkt startowy generatora liczb pseudolosowych
        // dzięki stałemu seed za każdym uruchomieniem dostajemy tę samą sekwencję liczb

        seeded = true;
    }
}

// wspólna funkcja do wypełniania struktury losowymi liczbami
template <typename Structure>
static bool fillRandomImpl(Structure& structure) {
    // template pozwala użyć tej samej logiki dla różnych struktur
    // Structure będzie tutaj zastąpione prawdziwym typem, np Array, SingleList albo DoubleList

    seedRandomOnce();

    // przechodzimy po całej strukturze i wpisujemy liczby losowe
    for (int i = 0; i < structure.getSize(); ++i) {
        if (!structure.set(i, std::rand())) {
            // std::rand zwraca kolejną liczbę z generatora
            // jeśli nie uda się zapisać wartości pod danym indeksem, kończymy błędem
            return false;
        }
    }

    return true;
}

// wspólna funkcja do kopiowania list
template <typename ListType>
static ListType* copyList(const ListType& source) {
    // tworzymy nową pustą listę
    ListType* copy = new (std::nothrow) ListType();
    // ListType* oznacza wskaźnik na obiekt listy
    // new tworzy obiekt w pamięci dynamicznej
    // std::nothrow oznacza, że przy braku pamięci dostaniemy nullptr zamiast wyjątku

    // jeśli nie udało się przydzielić pamięci, zwracamy nullptr
    if (copy == nullptr) {
        return nullptr;
    }

    // przepisujemy elementy z oryginalnej listy do nowej listy
    for (int i = 0; i < source.getSize(); ++i) {
        int value = 0;
        // value chwilowo przechowuje odczytaną liczbę

        if (!source.get(i, value)) {
            // jeśli nie udało się odczytać elementu z listy źródłowej
            // usuwamy już utworzoną kopię i kończymy
            delete copy;
            return nullptr;
        }

        if (!copy->pushBack(value)) {
            // pushBack dopisuje element na koniec nowej listy
            // strzałka -> służy do wywołania metody przez wskaźnik
            delete copy;
            return nullptr;
        }
    }

    return copy;
}

// wypełnia tablicę losowymi liczbami
bool RandomArrayGenerator::fillRandom(Array& array) {
    return fillRandomImpl(array);
}

// wypełnia listę jednokierunkową losowymi liczbami
bool RandomArrayGenerator::fillRandom(SingleList& list) {
    return fillRandomImpl(list);
}

// wypełnia listę dwukierunkową losowymi liczbami
bool RandomArrayGenerator::fillRandom(DoubleList& list) {
    return fillRandomImpl(list);
}

// tworzy kopię tablicy
Array* RandomArrayGenerator::copyArray(const Array& source) {
    // tworzymy nową tablicę o takim samym rozmiarze
    Array* copy = new (std::nothrow) Array(source.getSize());
    // Array nie jest kopiowany jak lista
    // tutaj trzeba od razu utworzyć tablicę o odpowiednim rozmiarze

    if (copy == nullptr) {
        return nullptr;
    }

    // przepisujemy wszystkie wartości do nowej tablicy
    for (int i = 0; i < source.getSize(); ++i) {
        int value = 0;

        if (!source.get(i, value)) {
            // jeśli odczyt się nie udał, usuwamy kopię i kończymy
            delete copy;
            return nullptr;
        }

        if (!copy->set(i, value)) {
            // jeśli zapis się nie udał, też usuwamy kopię i kończymy
            delete copy;
            return nullptr;
        }
    }

    return copy;
}

// tworzy kopię listy jednokierunkowej
SingleList* RandomArrayGenerator::copySingleList(const SingleList& source) {
    return copyList(source);
}

// tworzy kopię listy dwukierunkowej
DoubleList* RandomArrayGenerator::copyDoubleList(const DoubleList& source) {
    return copyList(source);
}