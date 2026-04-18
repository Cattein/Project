//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_FILEHANDLER_H
#define PROJECT_FILEHANDLER_H

#include <fstream>
#include <new>
#include <string>

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "structures/Stack.h"

// przestrzeń nazw z funkcjami do odczytu i zapisu struktur w pliku
namespace FileHandler {

    template <typename T>
    bool readValue(std::ifstream& file, T& value) {
        // dla większości typów używamy zwykłego operatora >>
        file >> value;
        return static_cast<bool>(file);
    }

    template <>
    inline bool readValue<std::string>(std::ifstream& file, std::string& value) {
        // std::ws pomija białe znaki przed właściwą linią
        // getline odczytuje cały wiersz, dzięki temu string może zawierać spacje
        std::getline(file >> std::ws, value);
        return static_cast<bool>(file);
    }

    // ===== stack =====

    // wczytuje stos z pliku i zwraca wskaźnik na utworzony obiekt
    template <typename T>
    Stack<T>* loadStackFromFile(const std::string& filename) {
        // const std::string& - nazwa pliku jest przekazywana bez kopiowania
        // const - funkcja nie może zmienić tej nazwy

        std::ifstream file(filename);
        // otwieramy plik do odczytu

        // jeśli plik nie został otwarty, zwracamy nullptr
        if (!file) {
            return nullptr;
        }

        int size = 0;
        file >> size;
        // odczytujemy liczbę elementów stosu

        // jeśli odczyt się nie udał albo rozmiar jest niepoprawny, kończymy działanie
        if (!file || size < 0) {
            return nullptr;
        }

        Stack<T>* stack = new (std::nothrow) Stack<T>();
        // Stack<T>* - wskaźnik na nowy obiekt stosu
        // std::nothrow - przy braku pamięci dostaniemy nullptr zamiast wyjątku

        if (stack == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne elementy stosu
        // wartości w pliku zapisujemy od dołu do góry,
        // dzięki temu zwykły push odtworzy poprawną kolejność
        for (int i = 0; i < size; ++i) {
            T value{};
            // {} oznacza domyślną inicjalizację zmiennej typu T

            if (!readValue(file, value)) {
                delete stack;
                return nullptr;
            }

            if (!stack->push(value)) {
                delete stack;
                return nullptr;
            }
        }

        return stack;
    }

    // zapisuje stos do pliku
    template <typename T>
    bool saveStackToFile(const Stack<T>& stack, const std::string& filename) {
        // const Stack<T>& - stos jest przekazywany przez referencję
        // const - funkcja nie może go zmieniać

        std::ofstream file(filename);
        // otwieramy plik do zapisu

        // jeśli nie udało się otworzyć pliku, zwracamy false
        if (!file) {
            return false;
        }

        file << stack.getSize() << '\n';
        // zapis liczby elementów stosu

        // zapisujemy elementy od dołu do góry,
        // żeby loadStackFromFile mogło poprawnie odtworzyć stos przez push
        for (int i = stack.getSize() - 1; i >= 0; --i) {
            T value{};

            if (!stack.get(i, value)) {
                return false;
            }

            file << value << '\n';
        }

        return true;
    }

    // ===== array =====

    // wczytuje tablicę z pliku, zwraca wskaźnik na utworzony obiekt
    template <typename T>
    Array<T>* loadArrayFromFile(const std::string& filename) {
        // const std::string& - nazwa pliku jest przekazywana przez referencję - nie tworzymy kopii napisu
        // const - funkcja nie może zmienić tej nazwy

        std::ifstream file(filename);
        // std::ifstream - otwieramy plik do odczytu

        // jeśli plik nie został otwarty, zwracamy nullptr
        if (!file) {
            return nullptr;
        }

        int size = 0;
        file >> size;
        // odczytujemy rozmiar tablicy zapisany w pliku

        // jeśli odczyt się nie udał albo rozmiar jest niepoprawny - kończymy działanie
        if (!file || size < 0) {
            return nullptr;
        }

        Array<T>* array = new (std::nothrow) Array<T>(size);
        // Array<T>* - wskaźnik na obiekt klasy Array
        // new - tworzenie obiektu w pamięci dynamicznej
        // std::nothrow - przy braku pamięci dostaniemy nullptr zamiast wyjątku

        // jeśli nie udało się przydzielić pamięci, zwracamy nullptr
        if (!array) {
            return nullptr;
        }

        // wczytujemy kolejne elementy tablicy
        for (int i = 0; i < size; ++i) {
            T value{};
            // {} oznacza domyślną inicjalizację zmiennej typu T

            if (!readValue(file, value)) {
                delete array;
                return nullptr;
            }

            // zapisujemy wartość do tablicy na odpowiedniej pozycji
            if (!array->set(i, value)) {
                delete array;
                return nullptr;
            }
        }

        // zwracamy gotową tablicę
        return array;
    }

    // zapisuje tablicę do pliku i zwraca true, jeśli zapis się udał
    template <typename T>
    bool saveArrayToFile(const Array<T>& array, const std::string& filename) {
        std::ofstream file(filename);
        // std::ofstream - otwieramy plik do zapisu

        // jeśli nie udało się otworzyć pliku, zwracamy false
        if (!file) {
            return false;
        }

        // zapisujemy rozmiar tablicy
        file << array.getSize() << '\n';

        // zapisujemy wszystkie elementy tablicy
        for (int i = 0; i < array.getSize(); ++i) {
            T value{};

            // pobieramy wartość z tablicy
            if (!array.get(i, value)) {
                return false;
            }

            // zapisujemy wartość do pliku
            file << value << '\n';
        }

        // zapis się udał
        return true;
    }

    // ===== single list =====

    // wczytuje listę jednokierunkową z pliku i zwraca wskaźnik na utworzony obiekt
    template <typename T>
    SingleList<T>* loadSingleListFromFile(const std::string& filename) {
        // wynik ma typ SingleList<T>* - funkcja zwraca wskaźnik na nowo utworzoną listę

        std::ifstream file(filename);
        // otwieramy plik do odczytu

        // jeśli plik nie został otwarty, zwracamy nullptr
        if (!file) {
            return nullptr;
        }

        int size = 0;
        file >> size;
        // odczytujemy liczbę elementów listy

        // jeśli odczyt się nie udał albo rozmiar jest niepoprawny, kończymy działanie
        if (!file || size < 0) {
            return nullptr;
        }

        // tworzymy nową pustą listę
        SingleList<T>* list = new (std::nothrow) SingleList<T>();

        // jeśli nie udało się przydzielić pamięci, zwracamy nullptr
        if (list == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne elementy listy
        for (int i = 0; i < size; ++i) {
            T value{};
            // {} oznacza domyślną inicjalizację zmiennej typu T

            if (!readValue(file, value)) {
                delete list;
                return nullptr;
            }

            // dopisujemy wartość na koniec listy
            if (!list->pushBack(value)) {
                delete list;
                return nullptr;
            }
        }

        return list;
    }

    // zapisuje listę jednokierunkową do pliku
    template <typename T>
    bool saveSingleListToFile(const SingleList<T>& list, const std::string& filename) {
        std::ofstream file(filename);
        // otwieramy plik do zapisu

        // jeśli nie udało się otworzyć pliku, zwracamy false
        if (!file) {
            return false;
        }

        // zapisujemy liczbę elementów listy
        file << list.getSize() << '\n';

        // zapisujemy wszystkie elementy listy
        for (int i = 0; i < list.getSize(); ++i) {
            T value{};

            // pobieramy wartość z listy
            if (!list.get(i, value)) {
                return false;
            }

            file << value << '\n';
            // zapisujemy wartość do pliku
        }

        return true;
    }

    // ===== double list =====

    // wczytuje listę dwukierunkową z pliku i zwraca wskaźnik na utworzony obiekt
    template <typename T>
    DoubleList<T>* loadDoubleListFromFile(const std::string& filename) {
        // const std::string& - nazwa pliku jest przekazywana bez kopiowania
        // const - funkcja nie może zmienić tej nazwy

        std::ifstream file(filename);
        // std::ifstream - odczyt danych z pliku

        // jeśli plik nie został poprawnie otwarty, zwracamy nullptr
        if (!file) {
            return nullptr;
        }

        int size = 0;
        file >> size;
        // odczyt liczby elementów zapisanych w pliku

        // jeśli odczyt się nie udał albo rozmiar jest ujemny, kończymy działanie
        if (!file || size < 0) {
            return nullptr;
        }

        DoubleList<T>* list = new (std::nothrow) DoubleList<T>();
        // DoubleList<T>* - wskaźnik na obiekt listy dwukierunkowej
        // new tworzy obiekt w pamięci dynamicznej
        // std::nothrow - przy braku pamięci dostaniemy nullptr zamiast wyjątku

        // jeśli nie udało się utworzyć listy, zwracamy nullptr
        if (list == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne wartości z pliku
        for (int i = 0; i < size; ++i) {
            T value{};
            // {} oznacza domyślną inicjalizację zmiennej typu T

            if (!readValue(file, value)) {
                delete list;
                return nullptr;
            }

            // dodajemy wartość na koniec listy
            // strzałka -> służy do dostępu do metod obiektu wskazywanego przez wskaźnik
            if (!list->pushBack(value)) {
                delete list;
                return nullptr;
            }
        }

        return list;
    }

    // zapisuje listę dwukierunkową do pliku
    template <typename T>
    bool saveDoubleListToFile(const DoubleList<T>& list, const std::string& filename) {
        // const DoubleList<T>& - lista jest przekazywana przez referencję - nie tworzymy kopii listy
        // const - funkcja nie może jej zmieniać

        std::ofstream file(filename);
        // std::ofstream - zapis danych do pliku

        // jeśli nie udało się otworzyć pliku, zwracamy false
        if (!file) {
            return false;
        }

        file << list.getSize() << '\n';
        // zapis liczby elementów listy

        // zapis wszystkich elementów listy
        for (int i = 0; i < list.getSize(); ++i) {
            T value{};

            // pobieramy wartość spod danego indeksu
            if (!list.get(i, value)) {
                return false;
            }

            file << value << '\n';
            // zapisujemy wartość do pliku
        }

        return true;
    }

} // namespace FileHandler

#endif // PROJECT_FILEHANDLER_H