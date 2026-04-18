//
// Created by MashaGuzhva on 12/04/2026.
//

#include "singleFile/SingleFileRunner.h"

#include <iostream>
#include <string>

#include "Parameters.h"
#include "file/FileHandler.h"
#include "algorytmsSorting/QuickSort.h"
#include "algorytmsSorting/ShellSort.h"
#include "algorytmsSorting/BucketSort.h"
#include "checking/SortingCheck.h"
#include "structures/Stack.h"
#include "structures/BinaryTree.h"

// sprawdza, czy wybrany wariant shella jest obsługiwany
static bool isShellParameterSupported() {
    return Parameters::shellParameter != Parameters::ShellParameters::option3 &&
           Parameters::shellParameter != Parameters::ShellParameters::option4;
}

// ===== wybór algorytmu dla tablicy =====

template <typename T>
static bool sortStructure(Array<T>& array) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(array, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(array, Parameters::shellParameter);
        return true;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented for Array.\n";
    return false;
}

static bool sortStructure(Array<int>& array) {
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        if (!BucketSort::sort(array)) {
            std::cerr << "ERROR! Bucket sort failed.\n";
            return false;
        }

        return true;
    }

    return sortStructure<int>(array);
}

// ===== wybór algorytmu dla listy jednokierunkowej =====

template <typename T>
static bool sortStructure(SingleList<T>& list) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }

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

static bool sortStructure(SingleList<int>& list) {
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        if (!BucketSort::sort(list)) {
            std::cerr << "ERROR! Bucket sort failed.\n";
            return false;
        }

        return true;
    }

    return sortStructure<int>(list);
}

// ===== wybór algorytmu dla listy dwukierunkowej =====

template <typename T>
static bool sortStructure(DoubleList<T>& list) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }

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

static bool sortStructure(DoubleList<int>& list) {
    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        if (!BucketSort::sort(list)) {
            std::cerr << "ERROR! Bucket sort failed.\n";
            return false;
        }

        return true;
    }

    return sortStructure<int>(list);
}

// ===== wybór algorytmu dla stosu =====

template <typename T>
static bool sortStructure(Stack<T>& stack) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(stack, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(stack, Parameters::shellParameter);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        std::cerr << "ERROR! Bucket sort is not implemented for Stack.\n";
        return false;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented for Stack.\n";
    return false;
}

// ===== wybór algorytmu dla drzewa binarnego =====

template <typename T>
static bool sortStructure(BinaryTree<T>& tree) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(tree, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(tree, Parameters::shellParameter);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        std::cerr << "ERROR! Bucket sort is not implemented for BinaryTree.\n";
        return false;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented for BinaryTree.\n";
    return false;
}

// ===== wspólna obsługa już wczytanej struktury =====

template <typename Structure>
static bool runLoadedStructure(
    Structure* structure,
    const std::string& structureName,
    bool (*saveFunc)(const Structure&, const std::string&)
) {
    // jeśli nie udało się wczytać struktury z pliku
    if (structure == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // uruchamiamy wybrane sortowanie
    if (!sortStructure(*structure)) {
        delete structure;
        return false;
    }

    // sprawdzamy, czy struktura jest naprawdę posortowana rosnąco
    if (!SortingCheck::SortedAscend(*structure)) {
        std::cerr << "ERROR! " << structureName << " is not sorted correctly.\n";
        delete structure;
        return false;
    }

    // jeśli użytkownik podał plik wyjściowy, zapisujemy wynik
    if (!Parameters::outputFile.empty()) {
        if (!saveFunc(*structure, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete structure;
            return false;
        }
    }

    // zwalniamy pamięć
    delete structure;
    return true;
}

// ===== obsługa single file dla tablicy =====

template <typename T>
static bool runArray() {
    return runLoadedStructure(
        FileHandler::loadArrayFromFile<T>(Parameters::inputFile),
        "Array",
        FileHandler::saveArrayToFile<T>
    );
}

// ===== obsługa single file dla listy jednokierunkowej =====

template <typename T>
static bool runSingleList() {
    return runLoadedStructure(
        FileHandler::loadSingleListFromFile<T>(Parameters::inputFile),
        "SingleList",
        FileHandler::saveSingleListToFile<T>
    );
}

// ===== obsługa single file dla listy dwukierunkowej =====

template <typename T>
static bool runDoubleList() {
    return runLoadedStructure(
        FileHandler::loadDoubleListFromFile<T>(Parameters::inputFile),
        "DoubleList",
        FileHandler::saveDoubleListToFile<T>
    );
}

// ===== obsługa single file dla stosu =====

template <typename T>
static bool runStack() {
    return runLoadedStructure(
        FileHandler::loadStackFromFile<T>(Parameters::inputFile),
        "Stack",
        FileHandler::saveStackToFile<T>
    );
}

// ===== obsługa single file dla drzewa binarnego =====

template <typename T>
static bool runBinaryTree() {
    return runLoadedStructure(
        FileHandler::loadBinaryTreeFromFile<T>(Parameters::inputFile),
        "BinaryTree",
        FileHandler::saveBinaryTreeToFile<T>
    );
}

bool SingleFileRunner::run() {
    // bez pliku wejściowego nie mamy czego wczytać
    if (Parameters::inputFile.empty()) {
        std::cerr << "ERROR! Input file is not set.\n";
        return false;
    }

    if (Parameters::algorithm == Parameters::Algorithms::quick &&
        Parameters::pivot == Parameters::Pivots::undefined) {
        std::cerr << "ERROR! pivot must be set for quick sort.\n";
        return false;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell &&
        Parameters::shellParameter == Parameters::ShellParameters::undefined) {
        std::cerr << "ERROR! shellParameter must be set for shell sort.\n";
        return false;
    }

    // ===== array =====

    if (Parameters::structure == Parameters::Structures::array) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runArray<int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runArray<float>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runArray<double>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeChar) {
            return runArray<char>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runArray<std::string>();
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runArray<unsigned int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) {
            return runArray<unsigned long>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) {
            return runArray<unsigned char>();
        }

        std::cerr << "ERROR! This data type is not implemented for Array.\n";
        return false;
    }

    // ===== single list =====

    if (Parameters::structure == Parameters::Structures::singleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runSingleList<int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runSingleList<float>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runSingleList<double>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeChar) {
            return runSingleList<char>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runSingleList<std::string>();
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runSingleList<unsigned int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) {
            return runSingleList<unsigned long>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) {
            return runSingleList<unsigned char>();
        }

        std::cerr << "ERROR! This data type is not implemented for SingleList.\n";
        return false;
    }

    // ===== double list =====

    if (Parameters::structure == Parameters::Structures::doubleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runDoubleList<int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runDoubleList<float>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runDoubleList<double>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeChar) {
            return runDoubleList<char>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runDoubleList<std::string>();
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runDoubleList<unsigned int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) {
            return runDoubleList<unsigned long>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) {
            return runDoubleList<unsigned char>();
        }

        std::cerr << "ERROR! This data type is not implemented for DoubleList.\n";
        return false;
    }

    // ===== stack =====

    if (Parameters::structure == Parameters::Structures::stack) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runStack<int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runStack<float>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runStack<double>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeChar) {
            return runStack<char>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runStack<std::string>();
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runStack<unsigned int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) {
            return runStack<unsigned long>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) {
            return runStack<unsigned char>();
        }

        std::cerr << "ERROR! This data type is not implemented for Stack.\n";
        return false;
    }

    // ===== binary tree =====

    if (Parameters::structure == Parameters::Structures::binaryTree) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runBinaryTree<int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runBinaryTree<float>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runBinaryTree<double>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeChar) {
            return runBinaryTree<char>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runBinaryTree<std::string>();
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runBinaryTree<unsigned int>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) {
            return runBinaryTree<unsigned long>();
        }

        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) {
            return runBinaryTree<unsigned char>();
        }

        std::cerr << "ERROR! This data type is not implemented for BinaryTree.\n";
        return false;
    }

    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}