#include <iostream>

#include "Parameters.h"

int main(int argc, char** argv)
{
    // Wczytanie argumentów programu.
    // Przekazujemy argc - 1 i argv + 1, ponieważ biblioteka oczekuje parametrów bez nazwy programu
    if (Parameters::readParameters(argc - 1, argv + 1) != 0) {
        std::cerr << "ERROR! Failed to read parameters.\n";
        Parameters::help();
        return 1;
    }

    // Tryb pomocy.
    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
        return 0;
    }

    // Tryb pojedynczego pliku.
    if (Parameters::runMode == Parameters::RunModes::singleFile) {
        std::cout << "singleFile mode selected\n";
        return 0;
    }

    // Tryb badań.
    if (Parameters::runMode == Parameters::RunModes::benchmark) {
        std::cout << "benchmark mode selected\n";
        return 0;
    }

    // Jeśli nie wybrano poprawnego trybu - błąd i help.
    std::cerr << "ERROR! Run mode is not set.\n";
    Parameters::help();
    return 1;
}