//
// Created by MashaGuzhva on 12/04/2026.
//
#include "singleFile/SingleFileRunner.h"

#include <iostream>

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
static bool sortArray(Array& array) {
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
        // bucket sort zwraca bool, więc sprawdzamy czy sortowanie się udało
        if (!BucketSort::sort(array)) {
            std::cerr << "ERROR! Bucket sort failed.\n";
            return false;
        }

        return true;
    }

    // jeśli wybrany algorytm nie jest jeszcze gotowy, kończymy z błędem
    std::cerr << "ERROR! Selected algorithm is not implemented.\n";
    return false;
}

// wybiera algorytm sortowania dla listy jednokierunkowej
static bool sortSingleList(SingleList& list) {
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

    // pozostałe algorytmy nie są jeszcze gotowe dla singlelist
    std::cerr << "ERROR! This algorithm is not implemented for SingleList yet.\n";
    return false;
}

// wybiera algorytm sortowania dla listy dwukierunkowej
static bool sortDoubleList(DoubleList& list) {
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

    // pozostałe algorytmy nie są jeszcze gotowe dla doublelist
    std::cerr << "ERROR! This algorithm is not implemented for DoubleList yet.\n";
    return false;
}

// obsługuje cały tryb single file dla tablicy
static bool runArray() {
    Array* array = FileHandler::loadArrayFromFile(Parameters::inputFile);
    // Array* oznacza wskaźnik na obiekt utworzony dynamicznie

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
static bool runSingleList() {
    SingleList* list = FileHandler::loadSingleListFromFile(Parameters::inputFile);
    // SingleList* oznacza wskaźnik na obiekt utworzony dynamicznie

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
static bool runDoubleList() {
    DoubleList* list = FileHandler::loadDoubleListFromFile(Parameters::inputFile);
    // DoubleList* oznacza wskaźnik na obiekt utworzony dynamicznie

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
    // na razie cały projekt działa tylko dla int
    if (Parameters::dataType != Parameters::DataTypes::typeInt) {
        std::cerr << "ERROR! Only int type is supported now.\n";
        return false;
    }

    // bez pliku wejściowego nie mamy czego wczytać
    if (Parameters::inputFile.empty()) {
        std::cerr << "ERROR! Input file is not set.\n";
        return false;
    }

    // wybieramy odpowiednią strukturę zależnie od parametrów
    if (Parameters::structure == Parameters::Structures::array) {
        return runArray();
    }

    if (Parameters::structure == Parameters::Structures::singleList) {
        return runSingleList();
    }

    if (Parameters::structure == Parameters::Structures::doubleList) {
        return runDoubleList();
    }

    // jeśli wybrana struktura nie jest jeszcze gotowa, kończymy z błędem
    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}}