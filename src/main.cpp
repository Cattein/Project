#include <iostream>

#include "Parameters.h"

#include "benchmark/BenchmarkRunner.h"
#include "benchmark/BenchmarkStats.h"
#include "singleFile/SingleFileRunner.h"
#include "benchmark/BenchmarkCsvWriter.h"

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
        if (!SingleFileRunner::run()) {
            return 1;
        }

        std::cout << "Sorting completed :)\n";
        return 0;
    }

    if (Parameters::runMode == Parameters::RunModes::benchmark) {
        if (Parameters::resultsFile.empty()) {
            std::cerr << "ERROR! resultsFile must be set in benchmark mode.\n";
            return 1;
        }

        BenchmarkStats stats{};

        if (!BenchmarkRunner::run(stats)) {
            return 1;
        }

        if (!BenchmarkCsvWriter::appendResult(Parameters::resultsFile, stats)) {
            std::cerr << "ERROR! Failed to save benchmark results to CSV.\n";
            return 1;
        }

        std::cout << "\nBenchmark completed :)\n\n";
        std::cout << "min [us] = " << stats.minTimeFinal << "\n";
        std::cout << "max [us] = " << stats.maxTimeFinal << "\n";
        std::cout << "avg [us] = " << stats.averageTimeFinal << "\n";
        std::cout << "Results saved to: " << Parameters::resultsFile << "\n";
        return 0;
    }

        // jeśli nie ustawiono poprawnego trybu, pokazujemy błąd i pomoc
        std::cerr << "ERROR! Run mode is not set.\n";
        Parameters::help();
        return 1;
    }
