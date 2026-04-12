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

        // rozmiar tablicy do testu musi być większy od 0
        if (Parameters::structureSize <= 0) {
            std::cerr << "ERROR! structureSize must be greater than 0.\n";
            return 1;
        }

        // liczba powtórzeń benchmarku musi być większa od 0
        if (Parameters::iterations <= 0) {
            std::cerr << "ERROR! iterations must be greater than 0.\n";
            return 1;
        }

        // tablicę źródłową
        Array source(Parameters::structureSize);

        // wypełniamy tablicę losowymi liczbami
        if (!RandomArrayGenerator::fillRandom(source)) {
            std::cerr << "ERROR! Failed to generate random data.\n";
            return 1;
        }

        // wykonujemy benchmark tyle razy, ile podano w iterations
        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy kopię tablicy źródłowej
            Array* testArray = RandomArrayGenerator::copyArray(source);

            // jeśli nie udało się zrobić kopii, kończymy z błędem
            if (testArray == nullptr) {
                std::cerr << "ERROR! Failed to copy source array.\n";
                return 1;
            }

            // zapisujemy moment startu sortowania
            auto start = std::chrono::steady_clock::now();
            // auto oznacza, że kompilator sam dobierze odpowiedni typ

            // wybieramy algorytm sortowania zależnie od parametrów
            if (Parameters::algorithm == Parameters::Algorithms::quick) {
                QuickSort::sort(*testArray, Parameters::pivot);
            }
            else if (Parameters::algorithm == Parameters::Algorithms::shell) {
                // na razie obsługiwane są tylko option1 i option2
                if (Parameters::shellParameter == Parameters::ShellParameters::option3 ||
                    Parameters::shellParameter == Parameters::ShellParameters::option4) {
                    std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                    delete testArray;
                    return 1;
                }

                ShellSort::sort(*testArray, Parameters::shellParameter);
            }
            else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
                // bucket sort zwraca bool, więc sprawdzamy czy sortowanie się udało
                if (!BucketSort::sort(*testArray)) {
                    std::cerr << "ERROR! Bucket sort failed.\n";
                    delete testArray;
                    return 1;
                }
            }
            else {
                // jeśli wybrany algorytm nie jest jeszcze gotowy, kończymy z błędem
                std::cerr << "ERROR! Selected algorithm is not implemented yet.\n";
                delete testArray;
                return 1;
            }

            // zapisujemy moment końca sortowania
            auto end = std::chrono::steady_clock::now();
            // auto oznacza, że kompilator sam dobierze odpowiedni typ

            // sprawdzamy, czy po sortowaniu tablica jest naprawdę rosnąca
            if (!SortingCheck::SortedAscend(*testArray)) {
                std::cerr << "ERROR! Array is not sorted correctly.\n";
                delete testArray;
                return 1;
            }

            // czas działania jednej iteracji w mikrosekundach
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            // wypisujemy czas dla aktualnej iteracji
            std::cout << "iteration " << (iteration + 1) << " [us] = " << elapsed.count() << "\n";
            delete testArray;     // po zakończeniu iteracji usuwamy kopię tablicy z pamięci

        }

        // jeśli wszystkie iteracje zakończyły się poprawnie, wypisujemy komunikat
        std::cout << "Benchmark completed successfully.\n";
        return 0;
    }

        // jeśli nie ustawiono poprawnego trybu, pokazujemy błąd i pomoc
        std::cerr << "ERROR! Run mode is not set.\n";
        Parameters::help();
        return 1;
    }
