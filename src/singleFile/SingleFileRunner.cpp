#include "singleFile/SingleFileRunner.h"

#include <iostream>

#include "Parameters.h"
#include "file/FileHandler.h"
#include "algorytmsSorting/QuickSort.h"
#include "algorytmsSorting/ShellSort.h"
#include "algorytmsSorting/BucketSort.h"
#include "checking/SortingCheck.h"

static bool isShellParameterSupported() {
    return Parameters::shellParameter != Parameters::ShellParameters::option3 &&
           Parameters::shellParameter != Parameters::ShellParameters::option4;
}

static bool sortArray(Array& array) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(array, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(array, Parameters::shellParameter);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        if (!BucketSort::sort(array)) {
            std::cerr << "ERROR! Bucket sort failed.\n";
            return false;
        }

        return true;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented.\n";
    return false;
}

static bool sortSingleList(SingleList& list) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(list, Parameters::shellParameter);
        return true;
    }

    std::cerr << "ERROR! This algorithm is not implemented for SingleList yet.\n";
    return false;
}

static bool sortDoubleList(DoubleList& list) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported.\n";
            return false;
        }

        ShellSort::sort(list, Parameters::shellParameter);
        return true;
    }

    std::cerr << "ERROR! This algorithm is not implemented for DoubleList yet.\n";
    return false;
}

static bool runArray() {
    Array* array = FileHandler::loadArrayFromFile(Parameters::inputFile);

    if (array == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    if (!sortArray(*array)) {
        delete array;
        return false;
    }

    if (!SortingCheck::SortedAscend(*array)) {
        std::cerr << "ERROR! Array is not sorted correctly.\n";
        delete array;
        return false;
    }

    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveArrayToFile(*array, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete array;
            return false;
        }
    }

    delete array;
    return true;
}

static bool runSingleList() {
    SingleList* list = FileHandler::loadSingleListFromFile(Parameters::inputFile);

    if (list == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    if (!sortSingleList(*list)) {
        delete list;
        return false;
    }

    if (!SortingCheck::SortedAscend(*list)) {
        std::cerr << "ERROR! SingleList is not sorted correctly.\n";
        delete list;
        return false;
    }

    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveSingleListToFile(*list, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete list;
            return false;
        }
    }

    delete list;
    return true;
}

static bool runDoubleList() {
    DoubleList* list = FileHandler::loadDoubleListFromFile(Parameters::inputFile);

    if (list == nullptr) {
        std::cerr << "ERROR! Failed to load input file.\n";
        return false;
    }

    if (!sortDoubleList(*list)) {
        delete list;
        return false;
    }

    if (!SortingCheck::SortedAscend(*list)) {
        std::cerr << "ERROR! DoubleList is not sorted correctly.\n";
        delete list;
        return false;
    }

    if (!Parameters::outputFile.empty()) {
        if (!FileHandler::saveDoubleListToFile(*list, Parameters::outputFile)) {
            std::cerr << "ERROR! Failed to save output file.\n";
            delete list;
            return false;
        }
    }

    delete list;
    return true;
}

bool SingleFileRunner::run() {
    if (Parameters::dataType != Parameters::DataTypes::typeInt) {
        std::cerr << "ERROR! Only int type is supported now.\n";
        return false;
    }

    if (Parameters::inputFile.empty()) {
        std::cerr << "ERROR! Input file is not set.\n";
        return false;
    }

    if (Parameters::structure == Parameters::Structures::array) {
        return runArray();
    }

    if (Parameters::structure == Parameters::Structures::singleList) {
        return runSingleList();
    }

    if (Parameters::structure == Parameters::Structures::doubleList) {
        return runDoubleList();
    }

    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}