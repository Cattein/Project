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

class RandomArrayGenerator {
private:
    // ustawia ziarno generatora tylko raz
    static void seedRandomOnce() {
        // static - zmienna seeded zostanie utworzona tylko raz
        // przy kolejnych wywołaniach funkcji zachowa swoją wcześniejszą wartość
        static bool seeded = false;

        if (!seeded) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            // std::time(nullptr) zwraca aktualny czas
            // dzięki temu przy każdym uruchomieniu programu seed będzie inny

            seeded = true;
        }
    }

    // ===== losowanie podstawowych typów =====

    // losuje wartość typu int
    static int randomInt() {
        // std::rand zwraca liczbę pseudolosową z zakresu od 0 do RAND_MAX
        // odejmujemy połowę RAND_MAX, żeby otrzymać także liczby ujemne
        return std::rand() - (RAND_MAX / 2);
    }

    // losuje wartość typu float
    static float randomFloat() {
        // zamieniamy wynik rand na liczbę z zakresu 0..1
        const float zeroToOne =
            static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        // static_cast<float> zamienia liczbę na typ float
        // dzięki temu dzielenie nie będzie całkowite

        // potem przesuwamy zakres do -1000000 .. 1000000
        return -1000000.0f + zeroToOne * 2000000.0f;
    }

    // losuje wartość typu double
    static double randomDouble() {
        // zamieniamy wynik rand na liczbę z zakresu 0..1
        const double zeroToOne =
            static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
        // static_cast<double> zamienia liczbę na typ double

        // potem przesuwamy zakres do -1000000 .. 1000000
        return -1000000.0 + zeroToOne * 2000000.0;
    }

    // losuje wartość typu unsigned int
    static unsigned int randomUnsignedInt() {
        // liczby bez znaku są zawsze dodatnie albo równe 0
        return static_cast<unsigned int>(std::rand());
    }

    // losuje wartość typu unsigned long
    static unsigned long randomUnsignedLong() {
        return static_cast<unsigned long>(std::rand());
    }

    // losuje wartość typu unsigned char
    static unsigned char randomUnsignedChar() {
        // % 256 daje zakres od 0 do 255
        return static_cast<unsigned char>(std::rand() % 256);
    }

    // losuje wartość typu char
    static char randomChar() {
        // zakres printable ascii: 32..126
        return static_cast<char>(32 + (std::rand() % 95));
    }

    // losuje napis z liter i cyfr
    static std::string randomString() {
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

    // ===== wybór losowej wartości zależnie od typu =====

    static int randomValueByType(int) {
        return randomInt();
    }

    static float randomValueByType(float) {
        return randomFloat();
    }

    static double randomValueByType(double) {
        return randomDouble();
    }

    static unsigned int randomValueByType(unsigned int) {
        return randomUnsignedInt();
    }

    static unsigned long randomValueByType(unsigned long) {
        return randomUnsignedLong();
    }

    static unsigned char randomValueByType(unsigned char) {
        return randomUnsignedChar();
    }

    static char randomValueByType(char) {
        return randomChar();
    }

    static std::string randomValueByType(std::string) {
        return randomString();
    }

    // wybiera odpowiednią funkcję losującą dla typu T
    template <typename T>
    static T randomValue() {
        return randomValueByType(T{});
    }

    // ===== wartości rosnące =====

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
        seedRandomOnce();

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

    // wspólna funkcja: najpierw losowo, potem pierwsza połowa rosnąco
    template <typename Structure, typename T>
    static bool fillAscending50PerImpl(Structure& structure) {
        if (!fillRandomImpl<Structure, T>(structure)) {
            return false;
        }

        return makeFirstHalfAscendingImpl<Structure, T>(structure);
    }

    // wspólna funkcja kopiowania dla struktur z pushBack
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

    template <typename T>
    static bool fillRandom(Array<T>& array) {
        // Array<T>& - tablica jest przekazywana przez referencję
        return fillRandomImpl<Array<T>, T>(array);
    }

    template <typename T>
    static bool fillRandom(SingleList<T>& list) {
        // SingleList<T>& - lista jest przekazywana przez referencję
        return fillRandomImpl<SingleList<T>, T>(list);
    }

    template <typename T>
    static bool fillRandom(DoubleList<T>& list) {
        // DoubleList<T>& - lista dwukierunkowa jest przekazywana przez referencję
        return fillRandomImpl<DoubleList<T>, T>(list);
    }

    template <typename T>
    static bool fillRandom(Stack<T>& stack) {
        return fillRandomImpl<Stack<T>, T>(stack);
    }

    template <typename T>
    static bool fillRandom(BinaryTree<T>& tree) {
        return fillRandomImpl<BinaryTree<T>, T>(tree);
    }

    // ===== fillAscending =====

    template <typename T>
    static bool fillAscending(Array<T>& array) {
        return fillAscendingImpl<Array<T>, T>(array);
    }

    template <typename T>
    static bool fillAscending(SingleList<T>& list) {
        return fillAscendingImpl<SingleList<T>, T>(list);
    }

    template <typename T>
    static bool fillAscending(DoubleList<T>& list) {
        return fillAscendingImpl<DoubleList<T>, T>(list);
    }

    template <typename T>
    static bool fillAscending(Stack<T>& stack) {
        return fillAscendingImpl<Stack<T>, T>(stack);
    }

    template <typename T>
    static bool fillAscending(BinaryTree<T>& tree) {
        return fillAscendingImpl<BinaryTree<T>, T>(tree);
    }

    // ===== fillDescending =====

    template <typename T>
    static bool fillDescending(Array<T>& array) {
        return fillDescendingImpl<Array<T>, T>(array);
    }

    template <typename T>
    static bool fillDescending(SingleList<T>& list) {
        return fillDescendingImpl<SingleList<T>, T>(list);
    }

    template <typename T>
    static bool fillDescending(DoubleList<T>& list) {
        return fillDescendingImpl<DoubleList<T>, T>(list);
    }

    template <typename T>
    static bool fillDescending(Stack<T>& stack) {
        return fillDescendingImpl<Stack<T>, T>(stack);
    }

    template <typename T>
    static bool fillDescending(BinaryTree<T>& tree) {
        return fillDescendingImpl<BinaryTree<T>, T>(tree);
    }

    // ===== fillAscending50Per =====

    template <typename T>
    static bool fillAscending50Per(Array<T>& array) {
        return fillAscending50PerImpl<Array<T>, T>(array);
    }

    template <typename T>
    static bool fillAscending50Per(SingleList<T>& list) {
        return fillAscending50PerImpl<SingleList<T>, T>(list);
    }

    template <typename T>
    static bool fillAscending50Per(DoubleList<T>& list) {
        return fillAscending50PerImpl<DoubleList<T>, T>(list);
    }

    template <typename T>
    static bool fillAscending50Per(Stack<T>& stack) {
        return fillAscending50PerImpl<Stack<T>, T>(stack);
    }

    template <typename T>
    static bool fillAscending50Per(BinaryTree<T>& tree) {
        return fillAscending50PerImpl<BinaryTree<T>, T>(tree);
    }

    // ===== copyArray =====

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

    template <typename T>
    static SingleList<T>* copySingleList(const SingleList<T>& source) {
        return copyPushBackStructureImpl<SingleList<T>, T>(source);
    }

    // ===== copyDoubleList =====

    template <typename T>
    static DoubleList<T>* copyDoubleList(const DoubleList<T>& source) {
        return copyPushBackStructureImpl<DoubleList<T>, T>(source);
    }

    // ===== copyBinaryTree =====

    template <typename T>
    static BinaryTree<T>* copyBinaryTree(const BinaryTree<T>& source) {
        return copyPushBackStructureImpl<BinaryTree<T>, T>(source);
    }

    // ===== copyStack =====

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