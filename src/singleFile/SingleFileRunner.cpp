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

bool SingleFileRunner::run() {

    // bez pliku wejściowego nie mamy czego wczytać
    if (Parameters::inputFile.empty()) {
        std::cerr << "ERROR! Input file is not set :-X \n";
        return false;
    }

    // wczytujemy tablicę z pliku
    // Array* oznacza wskaźnik na obiekt utworzony dynamicznie
    Array* array = FileHandler::loadArrayFromFile(Parameters::inputFile);

    // jeśli nie udało się wczytać danych
    if (array == nullptr) {
        std::cerr << "ERROR! Failed to load input file :о) \n";
        return false;
    }

    // wybieramy algorytm sortowania zależnie od parametrów
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        // *array oznacza, że przekazujemy sam obiekt, a nie wskaźnik

        QuickSort::sort(*array, Parameters::pivot);
    }
    else if (Parameters::algorithm == Parameters::Algorithms::shell) {

        // tylko option1 i option2
        if (Parameters::shellParameter == Parameters::ShellParameters::option3 ||
            Parameters::shellParameter == Parameters::ShellParameters::option4) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported\n";
            delete array;
            return false;
        }

        ShellSort::sort(*array, Parameters::shellParameter);
    }
    else if (Parameters::algorithm == Parameters::Algorithms::bucket) {

        // bucket sort zwraca bool, więc sprawdzamy czy sortowanie się udało
        if (!BucketSort::sort(*array)) {
            std::cerr << "ERROR! Bucket sort failed\n";
            delete array;
            return false;
        }
    }
    else {
        // jeśli wybrany algorytm nie jest jeszcze gotowy, kończymy z błędem
        std::cerr << "ERROR! Selected algorithm is not implemented :(\n";
        delete array;
        return false;
    }

    // po sortowaniu sprawdzamy, czy tablica jest naprawdę rosnąca
    if (!SortingCheck::SortedAscend(*array)) {
        std::cerr << "ERROR! Array is not sorted correctly :=)\n";
        delete array;
        return false;
    }

    // jeśli użytkownik podał plik wyjściowy, zapisujemy wynik
    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveArrayToFile(*array, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file\n";
            delete array;
            return false;
        }
    }

    // zwalniamy pamięć po zakończeniu pracy
    delete array;
    return true;
}