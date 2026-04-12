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
        std::cerr << "ERROR! Input file is not set.\n";
        return false;
    }

    // jeśli wybrano strukturę array
    if (Parameters::structure == Parameters::Structures::array) {

        // wczytujemy tablicę z pliku
        // Array* oznacza wskaźnik na obiekt utworzony dynamicznie
        Array* array = FileHandler::loadArrayFromFile(Parameters::inputFile);

        // jeśli nie udało się wczytać danych
        if (array == nullptr) {
            std::cerr << "ERROR! Failed to load input file.\n";
            return false;
        }

        // wybieramy algorytm sortowania zależnie od parametrów
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            // *array oznacza, że przekazujemy sam obiekt, a nie wskaźnik
            QuickSort::sort(*array, Parameters::pivot);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::shell) {

            // na razie obsługiwane są tylko option1 i option2
            if (Parameters::shellParameter == Parameters::ShellParameters::option3 ||
                Parameters::shellParameter == Parameters::ShellParameters::option4) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
                delete array;
                return false;
            }

            ShellSort::sort(*array, Parameters::shellParameter);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::bucket) {

            // bucket sort zwraca bool, więc sprawdzamy czy sortowanie się udało
            if (!BucketSort::sort(*array)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                delete array;
                return false;
            }
        }
        else {
            // jeśli wybrany algorytm nie jest jeszcze gotowy, kończymy z błędem
            std::cerr << "ERROR! Selected algorithm is not implemented.\n";
            delete array;
            return false;
        }

        // po sortowaniu sprawdzamy, czy tablica jest naprawdę rosnąca
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

        // zwalniamy pamięć po zakończeniu pracy
        delete array;
        return true;
    }

    // jeśli wybrano strukturę singlelist
    if (Parameters::structure == Parameters::Structures::singleList) {

        // wczytujemy listę jednokierunkową z pliku
        // SingleList* oznacza wskaźnik na obiekt utworzony dynamicznie
        SingleList* list = FileHandler::loadSingleListFromFile(Parameters::inputFile);

        // jeśli nie udało się wczytać danych
        if (list == nullptr) {
            std::cerr << "ERROR! Failed to load input file.\n";
            return false;
        }

        // na razie dla singlelist działa tylko quicksort
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort::sort(*list, Parameters::pivot);
        }
        else {
            std::cerr << "ERROR! This algorithm is not implemented for SingleList yet.\n";
            delete list;
            return false;
        }

        // po sortowaniu sprawdzamy, czy lista jest naprawdę rosnąca
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

        // zwalniamy pamięć po zakończeniu pracy
        delete list;
        return true;
    }

    // jeśli wybrana struktura nie jest jeszcze obsługiwana, kończymy z błędem
    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}