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

// sprawdza, czy wybrany wariant shella jest obsługiwany
static bool isShellParameterSupported() {
    return Parameters::shellParameter != Parameters::ShellParameters::option3 &&
           Parameters::shellParameter != Parameters::ShellParameters::option4;
}

// wybiera algorytm sortowania dla tablicy
template <typename T>
static bool sortArray(Array<T>& array) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(array, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        // na razie obsługiwane są tylko option1 i option2
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(array, Parameters::shellParameter);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        // bucket sort w tym projekcie działa na razie tylko dla int
        if constexpr (std::is_same_v<T, int>) {
            if (!BucketSort::sort(array)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        } else {
            std::cerr << "ERROR! Bucket sort is supported only for int type.\n";
            return false;
        }
    }

    // jeśli wybrany algorytm nie jest jeszcze gotowy, kończymy z błędem
    std::cerr << "ERROR! Selected algorithm is not implemented.\n";
    return false;
}

// wybiera algorytm sortowania dla listy jednokierunkowej
template <typename T>
static bool sortSingleList(SingleList<T>& list) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        // na razie obsługiwane są tylko option1 i option2
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(list, Parameters::shellParameter);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        // bucket sort w tym projekcie działa na razie tylko dla int
        if constexpr (std::is_same_v<T, int>) {
            if (!BucketSort::sort(list)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        } else {
            std::cerr << "ERROR! Bucket sort is supported only for int type.\n";
            return false;
        }
    }

    // pozostałe algorytmy nie są jeszcze gotowe dla singlelist
    std::cerr << "ERROR! This algorithm is not implemented for SingleList yet.\n";
    return false;
}

// wybiera algorytm sortowania dla listy dwukierunkowej
template <typename T>
static bool sortDoubleList(DoubleList<T>& list) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        // na razie obsługiwane są tylko option1 i option2
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(list, Parameters::shellParameter);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        // bucket sort w tym projekcie działa na razie tylko dla int
        if constexpr (std::is_same_v<T, int>) {
            if (!BucketSort::sort(list)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        } else {
            std::cerr << "ERROR! Bucket sort is supported only for int type.\n";
            return false;
        }
    }

    // pozostałe algorytmy nie są jeszcze gotowe dla doublelist
    std::cerr << "ERROR! This algorithm is not implemented for DoubleList yet.\n";
    return false;
}

// obsługuje cały tryb single file dla tablicy
template <typename T>
static bool runArray() {
    Array<T>* array = FileHandler::loadArrayFromFile<T>(Parameters::inputFile);
    // Array<T>* oznacza wskaźnik na obiekt utworzony dynamicznie

    if (array == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // uruchamiamy wybrane sortowanie
    if (!sortArray(*array)) {
        delete array;
        return false;
    }

    // sprawdzamy, czy po sortowaniu tablica jest naprawdę rosnąca
    if (!SortingCheck::SortedAscend(*array)) {
        std::cerr << "ERROR! Array is not sorted correctly.\n";
        delete array;
        return false;
    }

    // jeśli użytkownik podał plik wyjściowy, zapisujemy wynik
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveArrayToFile(*array, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete array;
            return false;
        }
    }

    // po zakończeniu pracy zwalniamy pamięć
    delete array;
    return true;
}

// obsługuje cały tryb single file dla listy jednokierunkowej
template <typename T>
static bool runSingleList() {
    SingleList<T>* list = FileHandler::loadSingleListFromFile<T>(Parameters::inputFile);
    // SingleList<T>* oznacza wskaźnik na obiekt utworzony dynamicznie

    if (list == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // uruchamiamy wybrane sortowanie
    if (!sortSingleList(*list)) {
        delete list;
        return false;
    }

    // sprawdzamy, czy po sortowaniu lista jest naprawdę rosnąca
    if (!SortingCheck::SortedAscend(*list)) {
        std::cerr << "ERROR! SingleList is not sorted correctly.\n";
        delete list;
        return false;
    }

    // jeśli użytkownik podał plik wyjściowy, zapisujemy wynik
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveSingleListToFile(*list, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete list;
            return false;
        }
    }

    // po zakończeniu pracy zwalniamy pamięć
    delete list;
    return true;
}

// obsługuje cały tryb single file dla listy dwukierunkowej
template <typename T>
static bool runDoubleList() {
    DoubleList<T>* list = FileHandler::loadDoubleListFromFile<T>(Parameters::inputFile);
    // DoubleList<T>* oznacza wskaźnik na obiekt utworzony dynamicznie

    if (list == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    // uruchamiamy wybrane sortowanie
    if (!sortDoubleList(*list)) {
        delete list;
        return false;
    }

    // sprawdzamy, czy po sortowaniu lista jest naprawdę rosnąca
    if (!SortingCheck::SortedAscend(*list)) {
        std::cerr << "ERROR! DoubleList is not sorted correctly.\n";
        delete list;
        return false;
    }

    // jeśli użytkownik podał plik wyjściowy, zapisujemy wynik
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveDoubleListToFile(*list, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete list;
            return false;
        }
    }

    // po zakończeniu pracy zwalniamy pamięć
    delete list;
    return true;
}

bool SingleFileRunner::run() {
    // bez pliku wejściowego nie mamy czego wczytać
    if (Parameters::inputFile.empty()) {
        std::cerr << "ERROR! Input file is not set.\n";
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

    // jeśli wybrana struktura nie jest jeszcze gotowa, kończymy z błędem
    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}