#include "benchmark/RandomArrayGenerator.h"

#include <new>
#include <cstdlib>

// stały seed
static void seedRandomOnce() {
    // static sprawia, że generator ustawiamy tylko raz
    static bool seeded = false;

    if (!seeded) {
        std::srand(12345);
        seeded = true;
    }
}

// wspólna funkcja do wypełniania struktury losowymi liczbami
template <typename Structure>
static bool fillRandomImpl(Structure& structure) {
    seedRandomOnce();

    // przechodzimy po całej strukturze i wpisujemy liczby losowe
    for (int i = 0; i < structure.getSize(); ++i) {
        if (!structure.set(i, std::rand())) {
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

    // jeśli nie udało się przydzielić pamięci, zwracamy nullptr
    if (copy == nullptr) {
        return nullptr;
    }

    // przepisujemy elementy z oryginalnej listy do nowej listy
    for (int i = 0; i < source.getSize(); ++i) {
        int value = 0;

        if (!source.get(i, value)) {
            delete copy;
            return nullptr;
        }

        if (!copy->pushBack(value)) {
            delete copy;
            return nullptr;
        }
    }

    return copy;
}

// ===== fillRandom =====

bool RandomArrayGenerator::fillRandom(Array& array) {
    return fillRandomImpl(array);
}

bool RandomArrayGenerator::fillRandom(SingleList& list) {
    return fillRandomImpl(list);
}

bool RandomArrayGenerator::fillRandom(DoubleList& list) {
    return fillRandomImpl(list);
}

// ===== copy =====

Array* RandomArrayGenerator::copyArray(const Array& source) {
    // tworzymy nową tablicę o takim samym rozmiarze
    Array* copy = new (std::nothrow) Array(source.getSize());

    if (copy == nullptr) {
        return nullptr;
    }

    // przepisujemy wszystkie wartości do nowej tablicy
    for (int i = 0; i < source.getSize(); ++i) {
        int value = 0;

        if (!source.get(i, value)) {
            delete copy;
            return nullptr;
        }

        if (!copy->set(i, value)) {
            delete copy;
            return nullptr;
        }
    }

    return copy;
}

SingleList* RandomArrayGenerator::copySingleList(const SingleList& source) {
    return copyList(source);
}

DoubleList* RandomArrayGenerator::copyDoubleList(const DoubleList& source) {
    return copyList(source);
}