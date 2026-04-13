//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_RANDOMARRAYGENERATOR_H
#define PROJECT_RANDOMARRAYGENERATOR_H

#include <new>
#include <cstdlib>
#include <string>
#include <random>

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"

class RandomArrayGenerator {
private:
    // ustawia ziarno generatora tylko raz
    static void seedRandomOnce() {
        // static oznacza, że zmienna seeded zostanie utworzona tylko raz
        // przy kolejnych wywołaniach funkcji zachowa swoją wcześniejszą wartość

        static bool seeded = false;

        if (!seeded) {
            std::srand(12345);
            // std::srand ustawia punkt startowy generatora std::rand
            // 12345 to seed, czyli wartość początkowa
            // dzięki stałemu seed przy każdym uruchomieniu programu
            // dostaniemy tę samą sekwencję liczb pseudolosowych
            // to jest wygodne przy badaniach i porównywaniu wyników

            seeded = true;
        }
    }

    // losuje wartość typu int
    static int randomInt() {
        // std::rand zwraca liczbę pseudolosową z zakresu od 0 do RAND_MAX
        // RAND_MAX to stała z biblioteki C/C++, określa maksymalną wartość rand()

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
        // 2000000 oznacza szerokość całego przedziału
        return -1000000.0f + zeroToOne * 2000000.0f;
    }

    // losuje wartość typu double
    static double randomDouble() {
        // zamieniamy wynik rand na liczbę z zakresu 0..1
        const double zeroToOne =
            static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
        // static_cast<double> zamienia liczbę na typ double
        // dzięki temu dzielenie nie będzie całkowite

        // potem przesuwamy zakres do -1000000 .. 1000000
        return -1000000.0 + zeroToOne * 2000000.0;
    }

    // losuje wartość typu unsigned int
    static unsigned int randomUnsignedInt() {
        // static_cast<unsigned int> zamienia wynik na typ bez znaku
        // tutaj liczby będą dodatnie albo równe 0
        return static_cast<unsigned int>(std::rand());
    }

    // losuje napis z liter i cyfr
    static std::string randomString() {
        const std::string characters =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        // const std::string oznacza, że po utworzeniu tego napisu
        // nie można już zmienić jego zawartości
        // characters zawiera wszystkie znaki, z których będziemy budować losowy napis

        // długość napisu od 1 do 20 znaków
        const int length = (std::rand() % 20) + 1;
        // % 20 daje zakres 0..19
        // +1 przesuwa ten zakres do 1..20

        static std::random_device randomDevice;
        // std::random_device służy do uzyskania wartości startowej
        // dla generatora liczb losowych

        static std::mt19937 generator(randomDevice());
        // std::mt19937 to generator liczb pseudolosowych z biblioteki C++
        // static oznacza, że generator tworzymy tylko raz
        // dzięki temu nie tworzymy nowego generatora przy każdym wywołaniu funkcji

        std::uniform_int_distribution<> distribution(
            0,
            static_cast<int>(characters.size()) - 1
        );
        // distribution losuje indeks znaku
        // 0 oznacza pierwszy znak w napisie characters
        // characters.size() - 1 oznacza ostatni poprawny indeks
        // static_cast<int> zamienia size_t na int

        std::string randomStringValue;
        // pusty napis, do którego będziemy dopisywać kolejne znaki

        for (int i = 0; i < length; ++i) {
            randomStringValue += characters[distribution(generator)];
            // losujemy indeks znaku i dopisujemy odpowiedni znak do napisu
        }

        return randomStringValue;
    }

public:
    // ===== fillRandom dla Array =====

    static bool fillRandom(Array<int>& array) {
        // Array<int>& - tablica jest przekazywana przez referencję
        // funkcja działa na oryginalnej tablicy, a nie na kopii

        seedRandomOnce();

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
        // SingleList<int>& - lista jest przekazywana przez referencję
        // funkcja wpisuje dane bezpośrednio do prawdziwej listy

        seedRandomOnce();

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
        // DoubleList<int>& - lista dwukierunkowa jest przekazywana przez referencję
        // funkcja zmienia prawdziwą strukturę danych

        seedRandomOnce();

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
        // template <typename T> oznacza, że funkcja działa dla różnych typów danych

        Array<T>* copy = new (std::nothrow) Array<T>(source.getSize());
        // Array<T>* - wskaźnik na nową dynamiczną tablicę
        // std::nothrow - przy braku pamięci dostaniemy nullptr zamiast wyjątku

        if (copy == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < source.getSize(); ++i) {
            T value{};
            // {} oznacza domyślną inicjalizację zmiennej typu T

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