#ifndef PROJECT_RANDOMARRAYGENERATOR_H
#define PROJECT_RANDOMARRAYGENERATOR_H

#include <new>
#include <cstdlib>
#include <ctime>
#include <string>
#include <type_traits>

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"

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
        // static_cast<unsigned int> zamienia wynik na typ bez znaku
        return static_cast<unsigned int>(std::rand());
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

    // zwraca losową wartość odpowiedniego typu
    template <typename T>
    static T randomValue() {
        if constexpr (std::is_same_v<T, int>) {
            return randomInt();
        } else if constexpr (std::is_same_v<T, float>) {
            return randomFloat();
        } else if constexpr (std::is_same_v<T, double>) {
            return randomDouble();
        } else if constexpr (std::is_same_v<T, unsigned int>) {
            return randomUnsignedInt();
        } else {
            return randomString();
        }
    }

    // zwraca wartość rosnącą dla różnych typów danych
    template <typename T>
    static T makeAscendingValue(int index) {
        if constexpr (std::is_same_v<T, std::string>) {
            return "str_" + std::to_string(index);
            // dla string tworzymy napisy str_0, str_1, str_2...
        } else {
            return static_cast<T>(index);
            // dla typów liczbowych zwracamy po prostu kolejne wartości
        }
    }

    // zwraca wartość malejącą dla różnych typów danych
    template <typename T>
    static T makeDescendingValue(int size, int index) {
        if constexpr (std::is_same_v<T, std::string>) {
            return "str_" + std::to_string(size - index);
            // dla string tworzymy napisy malejąco według numeru
        } else {
            return static_cast<T>(size - index);
            // dla typów liczbowych zwracamy wartości od większych do mniejszych
        }
    }

    // wspólna funkcja do wypełniania struktury losowo
    template <typename Structure, typename T>
    static bool fillRandomImpl(Structure& structure) {
        seedRandomOnce();

        for (int i = 0; i < structure.getSize(); ++i) {
            if (!structure.set(i, randomValue<T>())) {
                return false;
            }
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

public:
    // ===== fillRandom =====

    template <typename T>
    static bool fillRandom(Array<T>& array) {
        return fillRandomImpl<Array<T>, T>(array);
    }

    template <typename T>
    static bool fillRandom(SingleList<T>& list) {
        return fillRandomImpl<SingleList<T>, T>(list);
    }

    template <typename T>
    static bool fillRandom(DoubleList<T>& list) {
        return fillRandomImpl<DoubleList<T>, T>(list);
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

    // ===== copyArray =====

    template <typename T>
    static Array<T>* copyArray(const Array<T>& source) {
        // template <typename T> - funkcja działa dla różnych typów danych

        Array<T>* copy = new (std::nothrow) Array<T>(source.getSize());
        // Array<T>* - wskaźnik na nową dynamiczną tablicę
        // std::nothrow - przy braku pamięci dostaniemy nullptr zamiast wyjątku

        if (copy == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < source.getSize(); ++i) {
            T value{};
            // {} - domyślną inicjalizację zmiennej typu T

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
        SingleList<T>* copy = new (std::nothrow) SingleList<T>();
        // SingleList<T>* - wskaźnik na nowy obiekt listy

        if (copy == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < source.getSize(); ++i) {
            T value{};

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

    // ===== copyDoubleList =====

    template <typename T>
    static DoubleList<T>* copyDoubleList(const DoubleList<T>& source) {
        DoubleList<T>* copy = new (std::nothrow) DoubleList<T>();
        // DoubleList<T>* - wskaźnik na nowy obiekt listy

        if (copy == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < source.getSize(); ++i) {
            T value{};

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
};

#endif //PROJECT_RANDOMARRAYGENERATOR_H