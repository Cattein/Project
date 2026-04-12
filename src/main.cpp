#include <iostream>

#include "Parameters.h"
#include "file/FileHandler.h"
#include "algorytmsSorting/QuickSort.h"
#include "algorytmsSorting/ShellSort.h"
#include "checking/SortingCheck.h"
#include "algorytmsSorting/BucketSort.h"
#include <chrono>
#include <limits>
#include "benchmark/RandomArrayGenerator.h"



int main(int argc, char** argv) {
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

        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort::sort(*array, Parameters::pivot);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::shell) {
            if (Parameters::shellParameter == Parameters::ShellParameters::option3 ||
                Parameters::shellParameter == Parameters::ShellParameters::option4) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported\n";
                delete array;
                return 1;
                }

            ShellSort::sort(*array, Parameters::shellParameter);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if (!BucketSort::sort(*array)) {
                std::cerr << "ERROR! Bucket sort failed\n";
                delete array;
                return 1;
            }
            // po sortowaniu sprawdzamy, czy tablica jest rosnąca
            if (!SortingCheck::SortedAscend(*array)) {
                std::cerr << "ERROR! Array is not sorted correctly :=)\n";
                delete array;
                return 1;
            }
        }        else {
            std::cerr << "ERROR! Selected algorithm is not implemented :(\n";
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
        if (Parameters::structureSize <= 0) {
            std::cerr << "ERROR! structureSize must be greater than 0.\n";
            return 1;
        }

        if (Parameters::iterations <= 0) {
            std::cerr << "ERROR! iterations must be greater than 0.\n";
            return 1;
        }

        Array source(Parameters::structureSize);

        if (!RandomArrayGenerator::fillRandom(source)) {
            std::cerr << "ERROR! Failed to generate random data.\n";
            return 1;
        }
        // tablica o rozmiarze podanym w parametrach
        Array array(Parameters::structureSize);

        // generator liczb losowych tylko raz
        // static sprawia, że ta zmienna zapamiętuje swoją wartość między wywołaniami
        static bool seeded = false;

        // jeśli generator jeszcze nie był ustawiony, ustawiamy go aktualnym czasem
        if (!seeded) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            seeded = true;
        }

        // wypełniamy tablicę losowymi liczbami
        for (int i = 0; i < array.getSize(); ++i) {
            if (!array.set(i, std::rand())) {
                std::cerr << "ERROR! Failed to fill array with random data\n";
                return 1;
            }
        }

        // zapisujemy moment startu sortowania
        const auto start = std::chrono::high_resolution_clock::now();

        // wybieramy algorytm sortowania zależnie od parametrów
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort::sort(array, Parameters::pivot);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::shell) {

            // na razie obsługiwane są tylko option1 i option2
            if (Parameters::shellParameter == Parameters::ShellParameters::option3 ||
                Parameters::shellParameter == Parameters::ShellParameters::option4) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported\n";
                return 1;
            }

            ShellSort::sort(array, Parameters::shellParameter);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::bucket) {

            // bucket sort zwraca bool, więc sprawdzamy czy sortowanie się udało
            if (!BucketSort::sort(array)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return 1;
            }
        }
        else {
            // jeśli wybrany algorytm nie jest jeszcze gotowy, kończymy z błędem
            std::cerr << "ERROR! Selected algorithm is not implemented yet.\n";
            return 1;
        }

        // zapisujemy moment końca sortowania
        const auto end = std::chrono::high_resolution_clock::now();

        // sprawdzamy, czy po sortowaniu tablica jest naprawdę rosnąca
        if (!SortingCheck::SortedAscend(array)) {
            std::cerr << "ERROR! Array is not sorted correctly.\n";
            return 1;
        }

        // obliczamy czas działania w mikrosekundach
        const long long time =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // wypisujemy wynik benchmarku
        std::cout << "Benchmark completed successfully.\n";
        std::cout << "time [us] = " << time << "\n";

        return 0;
    }

        // jeśli nie ustawiono poprawnego trybu, pokazujemy błąd i pomoc
        std::cerr << "ERROR! Run mode is not set.\n";
        Parameters::help();
        return 1;
    }
