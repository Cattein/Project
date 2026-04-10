//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_FILEHANDLER_H
#define PROJECT_FILEHANDLER_H

#include <string>
#include "structures/Array.h"

// przestrzeń nazw z funkcjami do odczytu i zapisu tablicy w pliku
namespace FileHandler {

    // wczytuje tablicę z pliku, zwraca wskaźnik na utworzony obiekt
    Array* loadArrayFromFile(const std::string& filename);

    // zapisuje tablicę do pliku i zwraca true, jeśli zapis się udał
    bool saveArrayToFile(const Array& array, const std::string& filename);
}

#endif //PROJECT_FILEHANDLER_H