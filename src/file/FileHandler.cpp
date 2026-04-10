//
// Created by MashaGuzhva on 10/04/2026.
//

#include "file/FileHandler.h"

#include <fstream>
#include <new>

Array* FileHandler::loadArrayFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return nullptr;
    }

    int size;
    file >> size;
    if (!file || size < 0) {
        return nullptr;
    }

    Array* array = new (std::nothrow) Array(size);
    if (!array) {
        return nullptr;
    }

    for (int i = 0; i < size; ++i) {
        int value;
        file >> value;

        if (!file) {
            delete array;
            return nullptr;
        }

        array->set(i, value);
    }

    return array;
}

bool FileHandler::saveArrayToFile(const Array& array, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        return false;
    }

    file << array.getSize() << '\n';

    for (int i = 0; i < array.getSize(); ++i) {
        int value;
        if (!array.get(i, value)) {
            return false;
        }

        file << value << '\n';
    }

    return true;
}