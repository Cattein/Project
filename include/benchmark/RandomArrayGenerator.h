//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_RANDOMARRAYGENERATOR_H
#define PROJECT_RANDOMARRAYGENERATOR_H

#include <new>
#include <cstdlib>
#include <ctime>
#include <string>

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "structures/Stack.h"
#include "structures/BinaryTree.h"

// klasa pomocnicza do:
// - generowania danych w różnych układach
// - kopiowania struktur danych
class RandomArrayGenerator {
private:
    // ===== wybór losowej wartości zależnie od typu =====
    // poniższe przeciążone funkcje wybierają właściwy generator
    // na podstawie typu przekazanego argumentu

    static int randomValueByType(int) {
        // std::rand zwraca liczbę pseudolosową z zakresu od 0 do RAND_MAX
        // odejmujemy połowę RAND_MAX, żeby otrzymać także liczby ujemne
        return std::rand() - (RAND_MAX / 2);
    }

    static float randomValueByType(float) {
        // zamieniamy wynik rand na liczbę z zakresu 0..1
        const float zeroToOne =
            static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

        // potem przesuwamy zakres do -1000000 .. 1000000
        return -1000000.0f + zeroToOne * 2000000.0f;
    }

    static double randomValueByType(double) {
        // zamieniamy wynik rand na liczbę z zakresu 0..1
        const double zeroToOne =
            static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);

        // potem przesuwamy zakres do -1000000 .. 1000000
        return -1000000.0 + zeroToOne * 2000000.0;
    }

    static unsigned int randomValueByType(unsigned int) {
        // liczby bez znaku są zawsze dodatnie albo równe 0
        return static_cast<unsigned int>(std::rand());
    }

    static unsigned long randomValueByType(unsigned long) {
        return static_cast<unsigned long>(std::rand());
    }

    static unsigned char randomValueByType(unsigned char) {
        // % 256 daje zakres od 0 do 255
        return static_cast<unsigned char>(std::rand() % 256);
    }

    static char randomValueByType(char) {
        // zakres printable ascii: 32..126
        return static_cast<char>(32 + (std::rand() % 95));
    }

    static std::string randomValueByType(std::string) {
        const std::string characters =
                    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        // characters zawiera wszystkie znaki, z których będziemy budować losowy napis

        const int length = (std::rand() % 20) + 1;
        // długość napisu od 1 do 20 znaków

        std::string randomStringValue;
        // pusty napis, do którego będziemy dopisywać kolejne znaki

        for (int i = 0; i < length; ++i) {
            const int index = std::rand() % static_cast<int>(characters.size());
            // losujemy indeks znaku z napisu characters

            randomStringValue += characters[index];
            // dopisujemy wylosowany znak do napisu
        }

        return randomStringValue;
    }

    // wybiera odpowiednią funkcję losującą dla typu T
    template <typename T>
    static T randomValue() {
        return randomValueByType(T{});
    }

    // ===== wartości rosnące =====
    // poniższe funkcje tworzą dane już uporządkowane rosnąco

    static int makeAscendingValueByType(int index, int) {
        return index;
    }

    static float makeAscendingValueByType(int index, float) {
        return static_cast<float>(index);
    }

    static double makeAscendingValueByType(int index, double) {
        return static_cast<double>(index);
    }

    static unsigned int makeAscendingValueByType(int index, unsigned int) {
        return static_cast<unsigned int>(index);
    }

    static unsigned long makeAscendingValueByType(int index, unsigned long) {
        return static_cast<unsigned long>(index);
    }

    static unsigned char makeAscendingValueByType(int index, unsigned char) {
        return static_cast<unsigned char>(index % 256);
    }

    static char makeAscendingValueByType(int index, char) {
        // dla char używamy znaków printable
        return static_cast<char>(32 + (index % 95));
    }

    static std::string makeAscendingValueByType(int index, std::string) {
        // dla string tworzymy napisy str_0, str_1, str_2...
        return "str_" + std::to_string(index);
    }

    // zwraca wartość rosnącą dla typu T
    template <typename T>
    static T makeAscendingValue(int index) {
        return makeAscendingValueByType(index, T{});
    }

    // ===== wartości malejące =====
    // poniższe funkcje tworzą dane uporządkowane malejąco

    static int makeDescendingValueByType(int size, int index, int) {
        return size - index;
    }

    static float makeDescendingValueByType(int size, int index, float) {
        return static_cast<float>(size - index);
    }

    static double makeDescendingValueByType(int size, int index, double) {
        return static_cast<double>(size - index);
    }

    static unsigned int makeDescendingValueByType(int size, int index, unsigned int) {
        return static_cast<unsigned int>(size - index);
    }

    static unsigned long makeDescendingValueByType(int size, int index, unsigned long) {
        return static_cast<unsigned long>(size - index);
    }

    static unsigned char makeDescendingValueByType(int size, int index, unsigned char) {
        return static_cast<unsigned char>((size - index) % 256);
    }

    static char makeDescendingValueByType(int size, int index, char) {
        // dla char używamy znaków printable
        return static_cast<char>(32 + ((size - index) % 95));
    }

    static std::string makeDescendingValueByType(int size, int index, std::string) {
        // dla string tworzymy napisy malejąco według numeru
        return "str_" + std::to_string(size - index);
    }

    // zwraca wartość malejącą dla typu T
    template <typename T>
    static T makeDescendingValue(int size, int index) {
        return makeDescendingValueByType(size, index, T{});
    }

    // ===== wspólne funkcje wypełniania =====

    // wspólna funkcja do wypełniania struktury losowo
    template <typename Structure, typename T>
    static bool fillRandomImpl(Structure& structure) {
        // ustawiamy ziarno generatora tylko raz
        static bool seeded = false;

        if (!seeded) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            seeded = true;
        }

        for (int i = 0; i < structure.getSize(); ++i) {
            if (!structure.set(i, randomValue<T>())) {
                return false;
            }
            // set wpisuje wylosowaną wartość pod dany indeks
        }

        return true;
    }

    // wspólna funkcja do wypełniania struktury rosnąco
    template <typename Structure, typename T>
    static bool fillAscendingImpl(Structure& structure) {
        for (int i = 0; i < structure.getSize(); ++i) {
            if (!structure.set(i, makeAscendingValue<T>(i))) {
                return false;
            }
        }

        return true;
    }

    // wspólna funkcja do wypełniania struktury malejąco
    template <typename Structure, typename T>
    static bool fillDescendingImpl(Structure& structure) {
        const int size = structure.getSize();

        for (int i = 0; i < size; ++i) {
            if (!structure.set(i, makeDescendingValue<T>(size, i))) {
                return false;
            }
        }

        return true;
    }

    // ustawia pierwszą połowę struktury rosnąco
    template <typename Structure, typename T>
    static bool makeFirstHalfAscendingImpl(Structure& structure) {
        const int half = structure.getSize() / 2;
        // half oznacza połowę liczby elementów

        for (int i = 0; i < half; ++i) {
            if (!structure.set(i, makeAscendingValue<T>(i))) {
                return false;
            }
        }

        return true;
    }

    // wspólna funkcja:
    // najpierw wypełniamy strukturę losowo,
    // a potem pierwszą połowę ustawiamy rosnąco
    template <typename Structure, typename T>
    static bool fillAscending50PerImpl(Structure& structure) {
        if (!fillRandomImpl<Structure, T>(structure)) {
            return false;
        }

        return makeFirstHalfAscendingImpl<Structure, T>(structure);
    }

    // wspólna funkcja kopiowania dla struktur,
    // które można budować przez pushBack
    // działa dla: SingleList, DoubleList, BinaryTree
    template <typename Structure, typename T>
    static Structure* copyPushBackStructureImpl(const Structure& source) {
        Structure* copy = new (std::nothrow) Structure();
        // wskaźnik na nowy obiekt struktury

        if (copy == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < source.getSize(); ++i) {
            T value{};
            // {} - domyślna inicjalizacja zmiennej typu T

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

public:
    // ===== fillRandom =====

    // wypełnia tablicę losowymi wartościami
    template <typename T>
    static bool fillRandom(Array<T>& array) {
        return fillRandomImpl<Array<T>, T>(array);
    }

    // wypełnia listę jednokierunkową losowymi wartościami
    template <typename T>
    static bool fillRandom(SingleList<T>& list) {
        return fillRandomImpl<SingleList<T>, T>(list);
    }

    // wypełnia listę dwukierunkową losowymi wartościami
    template <typename T>
    static bool fillRandom(DoubleList<T>& list) {
        return fillRandomImpl<DoubleList<T>, T>(list);
    }

    // wypełnia stos losowymi wartościami
    template <typename T>
    static bool fillRandom(Stack<T>& stack) {
        return fillRandomImpl<Stack<T>, T>(stack);
    }

    // wypełnia drzewo binarne losowymi wartościami
    template <typename T>
    static bool fillRandom(BinaryTree<T>& tree) {
        return fillRandomImpl<BinaryTree<T>, T>(tree);
    }

    // ===== fillAscending =====

    // wypełnia tablicę wartościami rosnącymi
    template <typename T>
    static bool fillAscending(Array<T>& array) {
        return fillAscendingImpl<Array<T>, T>(array);
    }

    // wypełnia listę jednokierunkową wartościami rosnącymi
    template <typename T>
    static bool fillAscending(SingleList<T>& list) {
        return fillAscendingImpl<SingleList<T>, T>(list);
    }

    // wypełnia listę dwukierunkową wartościami rosnącymi
    template <typename T>
    static bool fillAscending(DoubleList<T>& list) {
        return fillAscendingImpl<DoubleList<T>, T>(list);
    }

    // wypełnia stos wartościami rosnącymi
    template <typename T>
    static bool fillAscending(Stack<T>& stack) {
        return fillAscendingImpl<Stack<T>, T>(stack);
    }

    // wypełnia drzewo binarne wartościami rosnącymi
    template <typename T>
    static bool fillAscending(BinaryTree<T>& tree) {
        return fillAscendingImpl<BinaryTree<T>, T>(tree);
    }

    // ===== fillDescending =====

    // wypełnia tablicę wartościami malejącymi
    template <typename T>
    static bool fillDescending(Array<T>& array) {
        return fillDescendingImpl<Array<T>, T>(array);
    }

    // wypełnia listę jednokierunkową wartościami malejącymi
    template <typename T>
    static bool fillDescending(SingleList<T>& list) {
        return fillDescendingImpl<SingleList<T>, T>(list);
    }

    // wypełnia listę dwukierunkową wartościami malejącymi
    template <typename T>
    static bool fillDescending(DoubleList<T>& list) {
        return fillDescendingImpl<DoubleList<T>, T>(list);
    }

    // wypełnia stos wartościami malejącymi
    template <typename T>
    static bool fillDescending(Stack<T>& stack) {
        return fillDescendingImpl<Stack<T>, T>(stack);
    }

    // wypełnia drzewo binarne wartościami malejącymi
    template <typename T>
    static bool fillDescending(BinaryTree<T>& tree) {
        return fillDescendingImpl<BinaryTree<T>, T>(tree);
    }

    // ===== fillAscending50Per =====

    // wypełnia tablicę tak, że pierwsza połowa jest rosnąca
    template <typename T>
    static bool fillAscending50Per(Array<T>& array) {
        return fillAscending50PerImpl<Array<T>, T>(array);
    }

    // wypełnia listę jednokierunkową tak, że pierwsza połowa jest rosnąca
    template <typename T>
    static bool fillAscending50Per(SingleList<T>& list) {
        return fillAscending50PerImpl<SingleList<T>, T>(list);
    }

    // wypełnia listę dwukierunkową tak, że pierwsza połowa jest rosnąca
    template <typename T>
    static bool fillAscending50Per(DoubleList<T>& list) {
        return fillAscending50PerImpl<DoubleList<T>, T>(list);
    }

    // wypełnia stos tak, że pierwsza połowa jest rosnąca
    template <typename T>
    static bool fillAscending50Per(Stack<T>& stack) {
        return fillAscending50PerImpl<Stack<T>, T>(stack);
    }

    // wypełnia drzewo binarne tak, że pierwsza połowa jest rosnąca
    template <typename T>
    static bool fillAscending50Per(BinaryTree<T>& tree) {
        return fillAscending50PerImpl<BinaryTree<T>, T>(tree);
    }

    // ===== copyArray =====

    // tworzy kopię tablicy
    template <typename T>
    static Array<T>* copyArray(const Array<T>& source) {
        Array<T>* copy = new (std::nothrow) Array<T>(source.getSize());
        // Array<T>* - wskaźnik na nową tablicę

        if (copy == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < source.getSize(); ++i) {
            T value{};

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

    // ===== copySingleList =====

    // tworzy kopię listy jednokierunkowej
    template <typename T>
    static SingleList<T>* copySingleList(const SingleList<T>& source) {
        return copyPushBackStructureImpl<SingleList<T>, T>(source);
    }

    // ===== copyDoubleList =====

    // tworzy kopię listy dwukierunkowej
    template <typename T>
    static DoubleList<T>* copyDoubleList(const DoubleList<T>& source) {
        return copyPushBackStructureImpl<DoubleList<T>, T>(source);
    }

    // ===== copyBinaryTree =====

    // tworzy kopię drzewa binarnego
    template <typename T>
    static BinaryTree<T>* copyBinaryTree(const BinaryTree<T>& source) {
        return copyPushBackStructureImpl<BinaryTree<T>, T>(source);
    }

    // ===== copyStack =====

    // tworzy kopię stosu
    template <typename T>
    static Stack<T>* copyStack(const Stack<T>& source) {
        Stack<T>* copy = new (std::nothrow) Stack<T>();
        // Stack<T>* - wskaźnik na nowy obiekt stosu

        if (copy == nullptr) {
            return nullptr;
        }

        // kopiujemy od najniższego elementu do szczytu,
        // żeby zachować tę samą kolejność w nowym stosie
        for (int i = source.getSize() - 1; i >= 0; --i) {
            T value{};

            if (!source.get(i, value)) {
                delete copy;
                return nullptr;
            }

            if (!copy->push(value)) {
                delete copy;
                return nullptr;
            }
        }

        return copy;
    }
};

#endif // PROJECT_RANDOMARRAYGENERATOR_H