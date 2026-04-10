//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_FILEHANDLER_H
#define PROJECT_FILEHANDLER_H

#include <string>
#include "structures/Array.h"

namespace FileHandler {

    Array* loadArrayFromFile(const std::string& filename);
    bool saveArrayToFile(const Array& array, const std::string& filename);
}








#endif //PROJECT_FILEHANDLER_H