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

    // wczytuje jedną wartość z pliku
    // dla większości typów używamy zwykłego operatora >>
    template <typename T>
    bool readValue(std::ifstream& file, T& value) {
        file >> value;
        return static_cast<bool>(file);
    }

    // specjalizacja dla std::string
    // getline odczytuje cały wiersz, więc string może zawierać spacje
    template <>
    inline bool readValue<std::string>(std::ifstream& file, std::string& value) {
        // std::ws pomija białe znaki przed właściwą linią
        std::getline(file >> std::ws, value);
        return static_cast<bool>(file);
    }

    // ===== wspólna funkcja wczytywania struktur z pushBack =====
    // działa dla: SingleList, DoubleList, BinaryTree
    // zakładamy, że dana struktura:
    // - ma pusty konstruktor
    // - ma metodę pushBack(...)
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

        // jeśli plik jest błędny albo rozmiar jest ujemny, kończymy
        if (!file || size < 0) {
            return nullptr;
        }

        Structure* structure = new (std::nothrow) Structure();
        // tworzymy nową pustą strukturę w pamięci dynamicznej

        if (structure == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne wartości i dopisujemy je na koniec struktury
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
    // zakładamy, że dana struktura:
    // - ma metodę getSize()
    // - ma metodę get(index, value)
    template <typename Structure, typename T>
    bool saveIndexedStructureToFileImpl(const Structure& structure, const std::string& filename) {
        std::ofstream file(filename);
        // otwieramy plik do zapisu

        if (!file) {
            return false;
        }

        file << structure.getSize() << '\n';
        // najpierw zapisujemy liczbę elementów

        // potem zapisujemy wszystkie elementy po kolei według indeksów
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
        std::ifstream file(filename);
        // otwieramy plik do odczytu

        if (!file) {
            return nullptr;
        }

        int size = 0;
        file >> size;
        // odczytujemy liczbę elementów stosu

        if (!file || size < 0) {
            return nullptr;
        }

        Stack<T>* stack = new (std::nothrow) Stack<T>();
        // tworzymy pusty stos w pamięci dynamicznej

        if (stack == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne elementy stosu
        // wartości w pliku zapisujemy od dołu do góry,
        // dzięki temu zwykły push odtworzy poprawną kolejność stosu
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
        std::ofstream file(filename);
        // otwieramy plik do zapisu

        if (!file) {
            return false;
        }

        file << stack.getSize() << '\n';
        // zapis liczby elementów stosu

        // zapisujemy elementy od dołu do góry,
        // żeby loadStackFromFile mogło poprawnie odtworzyć stos przez push
        for (int i = 0; i < stack.getSize(); ++i) {
            T value{};

            if (!stack.get(i, value)) {
                return false;
            }

            file << value << '\n';
        }

        return true;
    }

    // ===== binary tree =====

    // wczytuje drzewo binarne z pliku
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

    // wczytuje tablicę z pliku i zwraca wskaźnik na utworzony obiekt
    template <typename T>
    Array<T>* loadArrayFromFile(const std::string& filename) {
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
        // tworzymy tablicę o podanym rozmiarze

        if (array == nullptr) {
            return nullptr;
        }

        // wczytujemy kolejne elementy i zapisujemy je pod odpowiednimi indeksami
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
