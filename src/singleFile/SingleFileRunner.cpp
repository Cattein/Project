//
// Created by MashaGuzhva on 12/04/2026.
//

#include "singleFile/SingleFileRunner.h"

#include <iostream>
#include <string>
#include <type_traits>

#include "Parameters.h"
#include "file/FileHandler.h"
#include "algorytmsSorting/QuickSort.h"
#include "algorytmsSorting/ShellSort.h"
#include "algorytmsSorting/BucketSort.h"
#include "checking/SortingCheck.h"
#include "structures/Stack.h"
#include "structures/BinaryTree.h"

// sprawdza, czy wybrany wariant shellsorta jest obsługiwany
// na razie program wspiera tylko option1 i option2
static bool isShellParameterSupported() {
    return Parameters::shellParameter != Parameters::ShellParameters::option3 &&
           Parameters::shellParameter != Parameters::ShellParameters::option4;
}

// ===== wybór algorytmu dla tablicy =====

template <typename T>
static bool sortArray(Array<T>& array) {
    // bucket sort dla tablicy
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        if constexpr ((std::is_arithmetic<T>::value || std::is_same<T, std::string>::value)) {
            if (!BucketSort::sort(array)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        } else {
            std::cerr << "ERROR! Bucket sort works only for arithmetic data types and std::string.\n";
            return false;
        }
    }

    // quicksort dla tablicy
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(array, Parameters::pivot);
        return true;
    }

    // shellsort dla tablicy
    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(array, Parameters::shellParameter);
        return true;
    }

    // dla innych algorytmów tego typu tablicy nie obsługujemy tutaj
    std::cerr << "ERROR! Selected algorithm is not implemented for Array.\n";
    return false;
}

// ===== wybór algorytmu dla listy jednokierunkowej =====

template <typename T>
static bool sortSingleList(SingleList<T>& list) {
    // bucket sort dla listy jednokierunkowej
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        if constexpr ((std::is_arithmetic<T>::value || std::is_same<T, std::string>::value)) {
            if (!BucketSort::sort(list)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        } else {
            std::cerr << "ERROR! Bucket sort works only for arithmetic data types and std::string.\n";
            return false;
        }
    }

    // quicksort dla listy jednokierunkowej
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }

    // shellsort dla listy jednokierunkowej
    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(list, Parameters::shellParameter);
        return true;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented for SingleList.\n";
    return false;
}

// ===== wybór algorytmu dla listy dwukierunkowej =====

template <typename T>
static bool sortDoubleList(DoubleList<T>& list) {
    // bucket sort dla listy dwukierunkowej
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        if constexpr ((std::is_arithmetic<T>::value || std::is_same<T, std::string>::value)) {
            if (!BucketSort::sort(list)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        } else {
            std::cerr << "ERROR! Bucket sort works only for arithmetic data types and std::string.\n";
            return false;
        }
    }

    // quicksort dla listy dwukierunkowej
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }

    // shellsort dla listy dwukierunkowej
    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(list, Parameters::shellParameter);
        return true;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented for DoubleList.\n";
    return false;
}

// ===== wybór algorytmu dla stosu =====

template <typename T>
static bool sortStack(Stack<T>& stack) {
    // quicksort dla stosu
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(stack, Parameters::pivot);
        return true;
    }

    // shellsort dla stosu
    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(stack, Parameters::shellParameter);
        return true;
    }

    // bucket sort nie jest zaimplementowany dla stosu
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        std::cerr << "ERROR! Bucket sort is not implemented for Stack.\n";
        return false;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented for Stack.\n";
    return false;
}

// ===== wybór algorytmu dla drzewa binarnego =====

template <typename T>
static bool sortBinaryTree(BinaryTree<T>& tree) {
    // quicksort dla drzewa binarnego
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(tree, Parameters::pivot);
        return true;
    }

    // shellsort dla drzewa binarnego
    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(tree, Parameters::shellParameter);
        return true;
    }

    // bucket sort nie jest zaimplementowany dla drzewa
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        std::cerr << "ERROR! Bucket sort is not implemented for BinaryTree.\n";
        return false;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented for BinaryTree.\n";
    return false;
}

// ===== obsługa single file dla tablicy =====

template <typename T>
static bool runArray() {
    // wczytujemy tablicę z pliku wejściowego
    Array<T>* array = FileHandler::loadArrayFromFile<T>(Parameters::inputFile);

    if (array == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // uruchamiamy wybrane sortowanie
    if (!sortArray(*array)) {
        delete array;
        return false;
    }

    // sprawdzamy, czy wynik sortowania jest poprawny
    if (!SortingCheck::SortedAscend(*array)) {
        std::cerr << "ERROR! Array is not sorted correctly.\n";
        delete array;
        return false;
    }

    // jeśli podano plik wyjściowy, zapisujemy wynik
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveArrayToFile(*array, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete array;
            return false;
        }
    }

    // zwalniamy pamięć po zakończeniu pracy
    delete array;
    return true;
}

// ===== obsługa single file dla listy jednokierunkowej =====

template <typename T>
static bool runSingleList() {
    // wczytujemy listę z pliku
    SingleList<T>* list = FileHandler::loadSingleListFromFile<T>(Parameters::inputFile);

    if (list == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // sortujemy listę
    if (!sortSingleList(*list)) {
        delete list;
        return false;
    }

    // sprawdzamy poprawność sortowania
    if (!SortingCheck::SortedAscend(*list)) {
        std::cerr << "ERROR! SingleList is not sorted correctly.\n";
        delete list;
        return false;
    }

    // zapisujemy wynik do pliku, jeśli użytkownik podał nazwę
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveSingleListToFile(*list, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete list;
            return false;
        }
    }

    delete list;
    return true;
}

// ===== obsługa single file dla listy dwukierunkowej =====

template <typename T>
static bool runDoubleList() {
    // wczytujemy listę dwukierunkową z pliku
    DoubleList<T>* list = FileHandler::loadDoubleListFromFile<T>(Parameters::inputFile);

    if (list == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // sortujemy listę
    if (!sortDoubleList(*list)) {
        delete list;
        return false;
    }

    // sprawdzamy poprawność wyniku
    if (!SortingCheck::SortedAscend(*list)) {
        std::cerr << "ERROR! DoubleList is not sorted correctly.\n";
        delete list;
        return false;
    }

    // zapis wyniku do pliku wyjściowego
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveDoubleListToFile(*list, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete list;
            return false;
        }
    }

    delete list;
    return true;
}

// ===== obsługa single file dla stosu =====

template <typename T>
static bool runStack() {
    // wczytujemy stos z pliku
    Stack<T>* stack = FileHandler::loadStackFromFile<T>(Parameters::inputFile);

    if (stack == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // sortujemy stos
    if (!sortStack(*stack)) {
        delete stack;
        return false;
    }

    // sprawdzamy poprawność wyniku
    if (!SortingCheck::SortedAscend(*stack)) {
        std::cerr << "ERROR! Stack is not sorted correctly.\n";
        delete stack;
        return false;
    }

    // zapisujemy wynik do pliku wyjściowego
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveStackToFile(*stack, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete stack;
            return false;
        }
    }

    delete stack;
    return true;
}

// ===== obsługa single file dla drzewa binarnego =====

template <typename T>
static bool runBinaryTree() {
    // wczytujemy drzewo binarne z pliku
    BinaryTree<T>* tree = FileHandler::loadBinaryTreeFromFile<T>(Parameters::inputFile);

    if (tree == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // sortujemy drzewo
    if (!sortBinaryTree(*tree)) {
        delete tree;
        return false;
    }

    // sprawdzamy poprawność wyniku
    if (!SortingCheck::SortedAscend(*tree)) {
        std::cerr << "ERROR! BinaryTree is not sorted correctly.\n";
        delete tree;
        return false;
    }

    // zapisujemy wynik do pliku wyjściowego
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveBinaryTreeToFile(*tree, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete tree;
            return false;
        }
    }

    delete tree;
    return true;
}

bool SingleFileRunner::run() {
    // bez pliku wejściowego tryb single file nie może działać
    if (Parameters::inputFile.empty()) {
        std::cerr << "ERROR! Input file is not set.\n";
        return false;
    }

    // quicksort wymaga ustawionego pivota
    if (Parameters::algorithm == Parameters::Algorithms::quick &&
        Parameters::pivot == Parameters::Pivots::undefined) {
        std::cerr << "ERROR! pivot must be set for quick sort.\n";
        return false;
    }

    // shellsort wymaga ustawionego wariantu odstępów
    if (Parameters::algorithm == Parameters::Algorithms::shell &&
        Parameters::shellParameter == Parameters::ShellParameters::undefined) {
        std::cerr << "ERROR! shellParameter must be set for shell sort.\n";
        return false;
    }

    // ===== array =====
    // wybieramy odpowiedni typ danych dla tablicy

    if (Parameters::structure == Parameters::Structures::array) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runArray<int>();
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runArray<float>();
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runArray<double>();
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runArray<char>();
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runArray<std::string>();
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runArray<unsigned int>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runArray<unsigned long>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runArray<unsigned char>();

        std::cerr << "ERROR! This data type is not implemented for Array.\n";
        return false;
    }

    // ===== single list =====
    // wybieramy odpowiedni typ danych dla listy jednokierunkowej

    if (Parameters::structure == Parameters::Structures::singleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runSingleList<int>();
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runSingleList<float>();
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runSingleList<double>();
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runSingleList<char>();
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runSingleList<std::string>();
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runSingleList<unsigned int>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runSingleList<unsigned long>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runSingleList<unsigned char>();

        std::cerr << "ERROR! This data type is not implemented for SingleList.\n";
        return false;
    }

    // ===== double list =====
    // wybieramy odpowiedni typ danych dla listy dwukierunkowej

    if (Parameters::structure == Parameters::Structures::doubleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runDoubleList<int>();
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runDoubleList<float>();
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runDoubleList<double>();
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runDoubleList<char>();
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runDoubleList<std::string>();
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runDoubleList<unsigned int>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runDoubleList<unsigned long>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runDoubleList<unsigned char>();

        std::cerr << "ERROR! This data type is not implemented for DoubleList.\n";
        return false;
    }

    // ===== stack =====
    // wybieramy odpowiedni typ danych dla stosu

    if (Parameters::structure == Parameters::Structures::stack) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runStack<int>();
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runStack<float>();
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runStack<double>();
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runStack<char>();
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runStack<std::string>();
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runStack<unsigned int>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runStack<unsigned long>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runStack<unsigned char>();

        std::cerr << "ERROR! This data type is not implemented for Stack.\n";
        return false;
    }

    // ===== binary tree =====
    // wybieramy odpowiedni typ danych dla drzewa binarnego

    if (Parameters::structure == Parameters::Structures::binaryTree) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runBinaryTree<int>();
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runBinaryTree<float>();
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runBinaryTree<double>();
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runBinaryTree<char>();
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runBinaryTree<std::string>();
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runBinaryTree<unsigned int>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runBinaryTree<unsigned long>();
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runBinaryTree<unsigned char>();

        std::cerr << "ERROR! This data type is not implemented for BinaryTree.\n";
        return false;
    }

    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}