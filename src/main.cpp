#include <iostream>

#include "Parameters.h"
#include "benchmark/BenchmarkRunner.h"
#include "benchmark/BenchmarkStats.h"
#include "benchmark/BenchmarkCsvWriter.h"
#include "singleFile/SingleFileRunner.h"

int main(int argc, char** argv) {
    // argc - liczba wszystkich argumentów programu
    // argv - tablica argumentów tekstowych
    // argv[0] to nazwa programu

    // argc - 1 oraz argv + 1 pomijają nazwę programu,
    // więc funkcja czyta tylko prawdziwe parametry podane przez użytkownika
    if (Parameters::readParameters(argc - 1, argv + 1) != 0) {
        std::cerr << "ERROR! Failed to read parameters :-/ \n";
        Parameters::help();
        return 1;
    }

    // tryb help - wypisujemy pomoc i kończymy program poprawnie
    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
        return 0;
    }

    // tryb single file - wczytujemy jedną strukturę z pliku,
    // sortujemy ją i opcjonalnie zapisujemy wynik do pliku wyjściowego
    if (Parameters::runMode == Parameters::RunModes::singleFile) {
        if (!SingleFileRunner::run()) {
            return 1;
        }

        std::cout << "Sorting completed :)\n";
        return 0;
    }

    // tryb benchmark - wykonujemy serię pomiarów czasu sortowania
    if (Parameters::runMode == Parameters::RunModes::benchmark) {
        // bez nazwy pliku wynikowego nie mamy gdzie zapisać rezultatów
        if (Parameters::resultsFile.empty()) {
            std::cerr << "ERROR! resultsFile must be set in benchmark mode.\n";
            return 1;
        }

        BenchmarkStats stats{};
        // stats będzie przechowywać końcowe wyniki benchmarku:
        // czas minimalny, maksymalny i średni

        if (!BenchmarkRunner::run(stats)) {
            return 1;
        }

        // po wykonaniu benchmarku zapisujemy wyniki do pliku csv
        if (!BenchmarkCsvWriter::appendResult(Parameters::resultsFile, stats)) {
            std::cerr << "ERROR! Failed to save benchmark results to CSV.\n";
            return 1;
        }

        // wypisujemy krótkie podsumowanie na ekran
        std::cout << "\nBenchmark completed :)\n\n";
        std::cout << "min [us] = " << stats.minTimeFinal << "\n";
        std::cout << "max [us] = " << stats.maxTimeFinal << "\n";
        std::cout << "avg [us] = " << stats.averageTimeFinal << "\n";
        std::cout << "Results saved to: " << Parameters::resultsFile << "\n";
        return 0;
    }

    // jeśli użytkownik nie ustawił poprawnego trybu pracy, pokazujemy błąd i wypisujemy pomoc
    std::cerr << "ERROR! Run mode is not set.\n";
    Parameters::help();
    return 1;
}