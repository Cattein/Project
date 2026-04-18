#ifndef PROJECT_RANDOMARRAYGENERATOR_H
#define PROJECT_RANDOMARRAYGENERATOR_H

#include <new>
#include <cstdlib>
#include <ctime>
#include <string>

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

public:
    // ===== fillRandom dla Array =====

    static bool fillRandom(Array<int>& array) {
        seedRandomOnce();
        // Array<int>& - tablica jest przekazywana przez referencję
        // funkcja działa na oryginalnej tablicy, a nie na kopii
        for (int i = 0; i < array.getSize(); ++i) {
            if (!array.set(i, randomInt())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(Array<float>& array) {
        seedRandomOnce();
        for (int i = 0; i < array.getSize(); ++i) {
            if (!array.set(i, randomFloat())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(Array<double>& array) {
        seedRandomOnce();
        for (int i = 0; i < array.getSize(); ++i) {
            if (!array.set(i, randomDouble())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(Array<unsigned int>& array) {
        seedRandomOnce();
        for (int i = 0; i < array.getSize(); ++i) {
            if (!array.set(i, randomUnsignedInt())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(Array<std::string>& array) {
        seedRandomOnce();
        for (int i = 0; i < array.getSize(); ++i) {
            if (!array.set(i, randomString())) {
                return false;
            }
        }

        return true;
    }

    // ===== fillRandom dla SingleList =====

    static bool fillRandom(SingleList<int>& list) {
        seedRandomOnce();
        // SingleList<int>& - lista jest przekazywana przez referencję
        // funkcja wpisuje dane bezpośrednio do prawdziwej listy

        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomInt())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(SingleList<float>& list) {
        seedRandomOnce();
        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomFloat())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(SingleList<double>& list) {
        seedRandomOnce();
        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomDouble())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(SingleList<unsigned int>& list) {
        seedRandomOnce();
        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomUnsignedInt())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(SingleList<std::string>& list) {
        seedRandomOnce();
        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomString())) {
                return false;
            }
        }

        return true;
    }

    // ===== fillRandom dla DoubleList =====

    static bool fillRandom(DoubleList<int>& list) {
        seedRandomOnce();
        // DoubleList<int>& - lista dwukierunkowa jest przekazywana przez referencję
        // funkcja zmienia prawdziwą strukturę danych

        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomInt())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(DoubleList<float>& list) {
        seedRandomOnce();
        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomFloat())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(DoubleList<double>& list) {
        seedRandomOnce();
        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomDouble())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(DoubleList<unsigned int>& list) {
        seedRandomOnce();
        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomUnsignedInt())) {
                return false;
            }
        }

        return true;
    }

    static bool fillRandom(DoubleList<std::string>& list) {
        seedRandomOnce();
        for (int i = 0; i < list.getSize(); ++i) {
            if (!list.set(i, randomString())) {
                return false;
            }
        }

        return true;
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