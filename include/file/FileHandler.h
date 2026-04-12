//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_FILEHANDLER_H
#define PROJECT_FILEHANDLER_H

#include <string>
#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"

// przestrzeń nazw z funkcjami do odczytu i zapisu tablicy w pliku
namespace FileHandler {

    // wczytuje tablicę z pliku, zwraca wskaźnik na utworzony obiekt
    Array* loadArrayFromFile(const std::string& filename);

    // zapisuje tablicę do pliku i zwraca true, jeśli zapis się udał
    bool saveArrayToFile(const Array& array, const std::string& filename);

    // wczytuje listę jednokierunkową z pliku i zwraca wskaźnik na utworzony obiekt
    SingleList* loadSingleListFromFile(const std::string& filename);

    // zapisuje listę jednokierunkową do pliku
    bool saveSingleListToFile(const SingleList& list, const std::string& filename);

    // DoubleList* - wskaźnik na obiekt listy dwukierunkowej - tworzy nową listę na podstawie danych z pliku
    // const std::string& - nazwa pliku jest przekazywana bez kopiowania
    DoubleList* loadDoubleListFromFile(const std::string& filename);

    // const DoubleList& - funkcja tylko odczytuje listę i jej nie zmienia
    // zapisuje listę dwukierunkową do pliku
    bool saveDoubleListToFile(const DoubleList& list, const std::string& filename);


}

#endif //PROJECT_FILEHANDLER_H