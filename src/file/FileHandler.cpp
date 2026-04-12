//
// Created by MashaGuzhva on 10/04/2026.
//

#include "file/FileHandler.h"

#include <fstream>
#include <new>

// odczytuje dane tablicy z pliku
Array* FileHandler::loadArrayFromFile(const std::string& filename) {
    // const std::string& - nazwa pliku jest przekazywana przez referencję - nie tworzymy kopii napisu
    // const - funkcja nie może zmienić tej nazwy

    std::ifstream file(filename);    // otwieramy plik do odczytu

    // jeśli plik nie został otwarty, zwracamy nullptr
    if (!file) {
        return nullptr;
    }

    int size;
    file >> size;    // odczytujemy rozmiar tablicy zapisany w pliku

    // jeśli odczyt się nie udał albo rozmiar jest niepoprawny - kończymy działanie
    if (!file || size < 0) {
        return nullptr;
    }

    Array* array = new (std::nothrow) Array(size);    // tworzymy nową tablicę o podanym rozmiarze
    // Array* - wskaźnik na obiekt klasy Array
    // new - tworzenie obiektu w pamięci dynamicznej
    // std::nothrow - przy braku pamięci dostaniemy nullptr zamiast wyjątku

    // jeśli nie udało się przydzielić pamięci, zwracamy nullptr
    if (!array) {
        return nullptr;
    }

    // wczytujemy kolejne elementy tablicy
    for (int i = 0; i < size; ++i) {
        int value;


        file >> value;    // odczytujemy jedną wartość z pliku

        // jeśli danych jest za mało albo odczyt się nie udał, usuwamy tablicę
        if (!file) {
            delete array;
            return nullptr;
        }

        // zapisujemy wartość do tablicy na odpowiedniej pozycji
        if (!array->set(i, value)) {
            // array->set oznacza wywołanie metody przez wskaźnik
            //  -> służy  dostęp do pól i metod obiektu wskazywanego przez wskaźnik
            delete array;
            return nullptr;
        }
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

// odczytuje dane listy jednokierunkowej z pliku
SingleList* FileHandler::loadSingleListFromFile(const std::string& filename) {
    // wynik ma typ SingleList* - funkcja zwraca wskaźnik na nowo utworzoną listę

    std::ifstream file(filename);    // otwieramy plik do odczytu

    // jeśli plik nie został otwarty, zwracamy nullptr
    if (!file) {
        return nullptr;
    }

    int size = 0;
    file >> size;    // odczytujemy liczbę elementów listy

    // jeśli odczyt się nie udał albo rozmiar jest niepoprawny, kończymy działanie
    if (!file || size < 0) {
        return nullptr;
    }

    // tworzymy nową pustą listę
    SingleList* list = new (std::nothrow) SingleList();

    // jeśli nie udało się przydzielić pamięci, zwracamy nullptr
    if (list == nullptr) {
        return nullptr;
    }

    // wczytujemy kolejne elementy listy
    for (int i = 0; i < size; ++i) {
        int value = 0;
        file >> value;    // odczytujemy jedną wartość z pliku

        // jeśli odczyt się nie udał, usuwamy listę
        if (!file) {
            delete list;
            return nullptr;
        }

        // dopisujemy wartość na koniec listy
        if (!list->pushBack(value)) {
            delete list;
            return nullptr;
        }
    }

    return list;
}

// zapisuje listę jednokierunkową do pliku
bool FileHandler::saveSingleListToFile(const SingleList& list, const std::string& filename) {
    std::ofstream file(filename);    // otwieramy plik do zapisu

    // jeśli nie udało się otworzyć pliku, zwracamy false
    if (!file) {
        return false;
    }

    // zapisujemy liczbę elementów listy
    file << list.getSize() << '\n';

    // zapisujemy wszystkie elementy listy
    for (int i = 0; i < list.getSize(); ++i) {
        int value = 0;

        // pobieramy wartość z listy
        if (!list.get(i, value)) {
            return false;
        }

        file << value << '\n';    // zapisujemy wartość do pliku

    }

    return true;
}