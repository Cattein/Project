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
#include "structures/BinaryTree.h"

// przestrzeń nazw z funkcjami do odczytu i zapisu struktur w pliku
namespace FileHandler {

    // ===== odczyt pojedynczej wartości =====

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

    // ===== wspólna funkcja wczytywania struktur z pushBack =====
    // działa dla: SingleList, DoubleList, BinaryTree

    template <typename Structure, typename T>
    Structure* loadPushBackStructureFromFileImpl(const std::string& filename) {
        std::ifstream file(filename);
        // otwieramy plik do odczytu

        if (!file) {
            return nullptr;
        }

        int size = 0;
        file >> size;
        // odczytujemy liczbę elementów zapisanych w pliku

        if (!file || size < 0) {
            return nullptr;
        }

        Structure* structure = new (std::nothrow) Structure();
        // tworzymy nową pustą strukturę

        if (structure == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne wartości i dopisujemy na koniec
        for (int i = 0; i < size; ++i) {
            T value{};
            // {} oznacza domyślną inicjalizację zmiennej typu T

            if (!readValue(file, value)) {
                delete structure;
                return nullptr;
            }

            if (!structure->pushBack(value)) {
                delete structure;
                return nullptr;
            }
        }

        return structure;
    }

    // ===== wspólna funkcja zapisu struktur indeksowanych =====
    // działa dla: Array, SingleList, DoubleList, BinaryTree

    template <typename Structure, typename T>
    bool saveIndexedStructureToFileImpl(const Structure& structure, const std::string& filename) {
        std::ofstream file(filename);
        // otwieramy plik do zapisu

        if (!file) {
            return false;
        }

        file << structure.getSize() << '\n';
        // zapisujemy liczbę elementów

        // zapisujemy wszystkie elementy po indeksach
        for (int i = 0; i < structure.getSize(); ++i) {
            T value{};

            if (!structure.get(i, value)) {
                return false;
            }

            file << value << '\n';
        }

        return true;
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

        if (stack == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne elementy stosu
        // wartości w pliku zapisujemy od dołu do góry,
        // dzięki temu zwykły push odtworzy poprawną kolejność
        for (int i = 0; i < size; ++i) {
            T value{};

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

    // ===== binary tree =====

    // wczytuje drzewo binarne z pliku i zwraca wskaźnik na utworzony obiekt
    template <typename T>
    BinaryTree<T>* loadBinaryTreeFromFile(const std::string& filename) {
        // pushBack dodaje elementy poziomami,
        // więc odtworzymy tę samą strukturę drzewa
        return loadPushBackStructureFromFileImpl<BinaryTree<T>, T>(filename);
    }

    // zapisuje drzewo binarne do pliku
    template <typename T>
    bool saveBinaryTreeToFile(const BinaryTree<T>& tree, const std::string& filename) {
        return saveIndexedStructureToFileImpl<BinaryTree<T>, T>(tree, filename);
    }

    // ===== array =====

    // wczytuje tablicę z pliku, zwraca wskaźnik na utworzony obiekt
    template <typename T>
    Array<T>* loadArrayFromFile(const std::string& filename) {
        // const std::string& - nazwa pliku jest przekazywana przez referencję
        // const - funkcja nie może zmienić tej nazwy

        std::ifstream file(filename);
        // otwieramy plik do odczytu

        if (!file) {
            return nullptr;
        }

        int size = 0;
        file >> size;
        // odczytujemy rozmiar tablicy zapisany w pliku

        if (!file || size < 0) {
            return nullptr;
        }

        Array<T>* array = new (std::nothrow) Array<T>(size);
        // Array<T>* - wskaźnik na obiekt klasy Array

        if (array == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne elementy tablicy
        for (int i = 0; i < size; ++i) {
            T value{};

            if (!readValue(file, value)) {
                delete array;
                return nullptr;
            }

            if (!array->set(i, value)) {
                delete array;
                return nullptr;
            }
        }

        return array;
    }

    // zapisuje tablicę do pliku
    template <typename T>
    bool saveArrayToFile(const Array<T>& array, const std::string& filename) {
        return saveIndexedStructureToFileImpl<Array<T>, T>(array, filename);
    }

    // ===== single list =====

    // wczytuje listę jednokierunkową z pliku
    template <typename T>
    SingleList<T>* loadSingleListFromFile(const std::string& filename) {
        return loadPushBackStructureFromFileImpl<SingleList<T>, T>(filename);
    }

    // zapisuje listę jednokierunkową do pliku
    template <typename T>
    bool saveSingleListToFile(const SingleList<T>& list, const std::string& filename) {
        return saveIndexedStructureToFileImpl<SingleList<T>, T>(list, filename);
    }

    // ===== double list =====

    // wczytuje listę dwukierunkową z pliku
    template <typename T>
    DoubleList<T>* loadDoubleListFromFile(const std::string& filename) {
        return loadPushBackStructureFromFileImpl<DoubleList<T>, T>(filename);
    }

    // zapisuje listę dwukierunkową do pliku
    template <typename T>
    bool saveDoubleListToFile(const DoubleList<T>& list, const std::string& filename) {
        return saveIndexedStructureToFileImpl<DoubleList<T>, T>(list, filename);
    }

} // namespace FileHandler

#endif // PROJECT_FILEHANDLER_H