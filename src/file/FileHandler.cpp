//
// Created by MashaGuzhva on 10/04/2026.
//

#include "file/FileHandler.h"

#include <fstream>
#include <new>

// odczytuje dane tablicy z pliku
Array* FileHandler::loadArrayFromFile(const std::string& filename) {
    std::ifstream file(filename);    // otwieramy plik do odczytu


    // jeśli plik nie został otwarty, zwracamy nullptr
    if (!file) {
        return nullptr;
    }

    int size;
    file >> size;    // odczytujemy rozmiar tablicy zapisany w pliku


    // jeśli odczyt się nie udał albo rozmiar jest niepoprawny-kończymy działanie
    if (!file || size < 0) {
        return nullptr;
    }

    Array* array = new (std::nothrow) Array(size);    // tworzymy nową tablicę o podanym rozmiarze


    // jeśli nie udało się przydzielić pamięci, zwracamy nullptr
    if (!array) {
        return nullptr;
    }

    // wczytujemy kolejne elementy tablicy
    for (int i = 0; i < size; ++i) {
        int value;

        // odczytujemy jedną wartość z pliku
        file >> value;

        // jeśli danych jest za mało albo odczyt się nie udał, usuwamy tablicę
        if (!file) {
            delete array;
            return nullptr;
        }

        // zapisujemy wartość do tablicy na odpowiedniej pozycji
        array->set(i, value);
    }

    // zwracamy gotową tablicę
    return array;
}

// zapisuje tablicę do pliku
bool FileHandler::saveArrayToFile(const Array& array, const std::string& filename) {
    std::ofstream file(filename);    // otwieramy plik do zapisu


    // jeśli nie udało się otworzyć pliku, zwracamy false
    if (!file) {
        return false;
    }

    // zapisujemy rozmiar tablicy
    file << array.getSize() << '\n';

    // zapisujemy wszystkie elementy tablicy
    for (int i = 0; i < array.getSize(); ++i) {
        int value;

        // pobieramy wartość z tablicy
        if (!array.get(i, value)) {
            return false;
        }

        // zapisujemy wartość do pliku
        file << value << '\n';
    }

    // zapis się udał
    return true;
}