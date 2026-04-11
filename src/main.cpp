#include <iostream>

#include "Parameters.h"
#include "file/FileHandler.h"
#include "algorytmsSorting/QuickSort.h"
#include "checking/SortingCheck.h"

int main(int argc, char** argv){
    // argc - ile w sumie przekazano wierszy
    // char** argv -tablica argumentów (argv[0] = "Project.exe")

    // argc - 1 i argv + 1 pomijają nazwę programu - Project.exe
    if (Parameters::readParameters(argc - 1, argv + 1) != 0) {
        std::cerr << "ERROR! Failed to read parameters :-/ \n";
        Parameters::help();
        return 1;
    }

    // jeśli użytkownik wybrał help
    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
        return 0;
    }

    //  singleFile - sortowanie danych z jednego pliku
    if (Parameters::runMode == Parameters::RunModes::singleFile) {

        // quick sort
        if (Parameters::algorithm != Parameters::Algorithms::quick) {
            std::cerr << "ERROR! Only quick sort is supported now.\n";
            return 1;
        }

        // struktura array
        if (Parameters::structure != Parameters::Structures::array) {
            std::cerr << "ERROR! Only array structure is supported now\n";
            return 1;
        }

        // typ int
        if (Parameters::dataType != Parameters::DataTypes::typeInt) {
            std::cerr << "ERROR! Only int type is supported\n";
            return 1;
        }

        // bez pliku wejściowego nie mamy czego wczytać
        if (Parameters::inputFile.empty()) {
            std::cerr << "ERROR! Input file is not set :-X \n";
            return 1;
        }

        // wczytujemy tablicę z pliku
        // Array* oznacza wskaźnik na obiekt utworzony dynamicznie
        Array* array = FileHandler::loadArrayFromFile(Parameters::inputFile);

        // jeśli nie udało się wczytać danych
        if (array == nullptr) {
            std::cerr << "ERROR! Failed to load input file :о) \n";
            return 1;
        }

        // *array oznacza, że przekazujemy sam obiekt, a nie wskaźnik
        QuickSort::sort(*array);

        // po sortowaniu sprawdzamy, czy tablica jest rosnąca
        if (!SortingCheck::SortedAscend(*array)) {
            std::cerr << "ERROR! Array is not sorted correctly :=)\n";
            delete array;
            return 1;
        }

        // jeśli użytkownik podał plik wyjściowy, zapisujemy wynik
        if (!Parameters::outputFile.empty()) {
            if (!FileHandler::saveArrayToFile(*array, Parameters::outputFile)) {
                std::cerr << "ERROR! Failed to save output file :-C\n";
                delete array;
                return 1;
            }
        }

        delete array;   // zwalniamy pamięć po zakończeniu pracy


        std::cout << "Sorting completed :)\n";
        return 0;
    }

    // ten tryb jest przewidziany, ale jeszcze nie został zrobiony
    if (Parameters::runMode == Parameters::RunModes::benchmark) {
        std::cout << "Benchmark mode is not implemented yet.\n";
        return 0;
    }

    // jeśli nie ustawiono poprawnego trybu, pokazujemy błąd i pomoc
    std::cerr << "ERROR! Run mode is not set.\n";
    Parameters::help();
    return 1;
}