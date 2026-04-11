#include <iostream>

#include "file/FileHandler.h"
#include "algorytmsSorting/QuickSort.h"
#include "checking/SortingCheck.h"

int main() {
    Array* array = FileHandler::loadArrayFromFile("../file.txt");

    if (array == nullptr) {
        std::cerr << "ERROR! Failed to load file.\n";
        return 1;
    }

    std::cout << "Loaded values before sorting:\n";
    for (int i = 0; i < array->getSize(); ++i) {
        int value = 0;
        if (!array->get(i, value)) {
            std::cerr << "ERROR! Failed to read value from array.\n";
            delete array;
            return 1;
        }
        std::cout << value << " ";
    }
    std::cout << "\n";

    QuickSort::sort(*array);

    if (!SortingCheck::SortedAscend(*array)) {
        std::cerr << "ERROR! Array is not sorted correctly.\n";
        delete array;
        return 1;
    }

    std::cout << "Values after sorting:\n";
    for (int i = 0; i < array->getSize(); ++i) {
        int value = 0;
        if (!array->get(i, value)) {
            std::cerr << "ERROR! Failed to read value from array.\n";
            delete array;
            return 1;
        }
        std::cout << value << " ";
    }
    std::cout << "\n";

    if (!FileHandler::saveArrayToFile(*array, "../output.txt")) {
        std::cerr << "ERROR! Failed to save file.\n";
        delete array;
        return 1;
    }

    std::cout << "Sorted data saved to output.txt\n";

    delete array;
    return 0;
}