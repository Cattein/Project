//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_RANDOMARRAYGENERATOR_H
#define PROJECT_RANDOMARRAYGENERATOR_H

#include <new>
#include <random>
#include <string>
#include <limits>

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
    // wspólny generator liczb losowych
    // tworzy się tylko raz i potem jest używany przy każdym losowaniu
    static std::mt19937& generator() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    // ===== wybór losowej wartości zależnie od typu =====
    // poniższe przeciążone funkcje wybierają właściwy generator
    // na podstawie typu przekazanego argumentu

    static int randomValueByType(int) {
        // losujemy liczbę int z pełnego zakresu typu
        std::uniform_int_distribution<int> dist(
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max()
        );

        return dist(generator());
    }

    static float randomValueByType(float) {
        // losujemy liczbę float z pełnego zakresu typu
        std::uniform_real_distribution<float> dist(
            std::numeric_limits<float>::lowest(),
            std::numeric_limits<float>::max()
        );

        return dist(generator());
    }

    static double randomValueByType(double) {
        // losujemy liczbę double z pełnego zakresu typu
        std::uniform_real_distribution<double> dist(
            std::numeric_limits<double>::lowest(),
            std::numeric_limits<double>::max()
        );

        return dist(generator());
    }

    static unsigned int randomValueByType(unsigned int) {
        // liczby bez znaku losujemy od 0 do maksymalnej wartości typu
        std::uniform_int_distribution<unsigned int> dist(
            std::numeric_limits<unsigned int>::min(),
            std::numeric_limits<unsigned int>::max()
        );

        return dist(generator());
    }

    static unsigned long randomValueByType(unsigned long) {
        std::uniform_int_distribution<unsigned long> dist(
            std::numeric_limits<unsigned long>::min(),
            std::numeric_limits<unsigned long>::max()
        );

        return dist(generator());
    }

    static unsigned char randomValueByType(unsigned char) {
        // dla unsigned char używamy int jako typu pomocniczego do losowania,
        // a potem wynik zamieniamy na unsigned char
        std::uniform_int_distribution<int> dist(
            static_cast<int>(std::numeric_limits<unsigned char>::min()),
            static_cast<int>(std::numeric_limits<unsigned char>::max())
        );

        return static_cast<unsigned char>(dist(generator()));
    }

    static char randomValueByType(char) {
        // dla char losujemy tylko znaki printable ascii: 32..126
        // dzięki temu znak można bezpiecznie zapisać do pliku tekstowego
        std::uniform_int_distribution<int> dist(32, 126);
        return static_cast<char>(dist(generator()));
    }

    static std::string randomValueByType(const std::string&) {
        // zbiór znaków printable, z których budujemy losowy napis
        const std::string characters =
            "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

        // długość napisu od 1 do 20 znaków
        std::uniform_int_distribution<int> lengthDist(1, 20);

        // losowanie indeksu znaku z napisu characters
        std::uniform_int_distribution<int> charDist(0, static_cast<int>(characters.size()) - 1);

        const int length = lengthDist(generator());

        std::string randomStringValue;
        // pusty napis, do którego będziemy dopisywać kolejne znaki

        for (int i = 0; i < length; ++i) {
            randomStringValue += characters[charDist(generator())];
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
        if (index > 255) {
            index = 255;
        }

        return static_cast<unsigned char>(index);
    }

    static char makeAscendingValueByType(int index, char) {
        int value = 32 + index;

        if (value > 126) {
            value = 126;
        }

        return static_cast<char>(value);
    }

    static std::string makeAscendingValueByType(int index, const std::string&) {
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
        int value = size - index;

        if (value < 0) {
            value = 0;
        }

        if (value > 255) {
            value = 255;
        }

        return static_cast<unsigned char>(value);
    }

    static char makeDescendingValueByType(int size, int index, char) {
        int value = 32 + (size - index);

        if (value > 126) {
            value = 126;
        }

        if (value < 32) {
            value = 32;
        }

        return static_cast<char>(value);
    }

    static std::string makeDescendingValueByType(int size, int index, const std::string&) {
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
    // korzysta z funkcji randomValue<T>(), która dobiera właściwy zakres dla danego typu
    template <typename Structure, typename T>
    static bool fillRandomImpl(Structure& structure) {
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