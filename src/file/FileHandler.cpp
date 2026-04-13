//
// Created by MashaGuzhva on 10/04/2026.
//

#include "file/FileHandler.h"

#include <fstream>
#include <new>

// odczytuje dane tablicy z pliku
Array<int>* FileHandler::loadArrayFromFile(const std::string& filename) {
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

    Array<int>* array = new (std::nothrow) Array<int>(size);    // tworzymy nową tablicę o podanym rozmiarze
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
            // array->set - wywołanie metody przez wskaźnik
            //  -> służy  dostęp do pól i metod obiektu wskazywanego przez wskaźnik
            delete array;
            return nullptr;
        }
    }

    // zwracamy gotową tablicę
    return array;
}

// zapisuje tablicę do pliku
bool FileHandler::saveArrayToFile(const Array<int>& array, const std::string& filename) {
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
SingleList<int>* FileHandler::loadSingleListFromFile(const std::string& filename) {
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
    SingleList<int>* list = new (std::nothrow) SingleList<int>();

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
bool FileHandler::saveSingleListToFile(const SingleList<int>& list, const std::string& filename) {
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

// odczytuje listę dwukierunkową z pliku
DoubleList<int>* FileHandler::loadDoubleListFromFile(const std::string& filename) {
    // const std::string& - nazwa pliku jest przekazywana bez kopiowania
    // const - funkcja nie może zmienić tej nazwy
    std::ifstream file(filename);
    // std::ifstream - odczyt danych z pliku

    // jeśli plik nie został poprawnie otwarty, zwracamy nullptr
    if (!file) {
        return nullptr;
    }

    int size = 0;
    file >> size;    // odczyt liczbę elementów zapisanych w pliku


    // jeśli odczyt się nie udał albo rozmiar jest ujemny, kończymy działanie
    if (!file || size < 0) {
        return nullptr;
    }

    DoubleList<int>* list = new (std::nothrow) DoubleList<int>();
    // DoubleList* - wskaźnik na obiekt listy dwukierunkowej
    // new tworzy obiekt w pamięci dynamicznej
    // std::nothrow - przy braku pamięci dostaniemy nullptr zamiast wyjątku

    // jeśli nie udało się utworzyć listy, zwracamy nullptr
    if (list == nullptr) {
        return nullptr;
    }

    // wczytujemy kolejne wartości z pliku
    for (int i = 0; i < size; ++i) {
        int value = 0;
        file >> value;    // odczytujemy jedną wartość z pliku


        // jeśli odczyt się nie udał, usuwamy listę i kończymy
        if (!file) {
            delete list;     // delete zwalnia pamięć po obiekcie utworzonym przez new
            return nullptr;
        }

        // dodajemy wartość na koniec listy
        // strzałka -> - dostępu do metod obiektu wskazywanego przez wskaźnik
        if (!list->pushBack(value)) {    //wywołanie metody przez wskaźnik
            delete list;
            return nullptr;
        }
    }

    return list;    // zwracamy gotową listę

}

// zapisuje listę dwukierunkową do pliku
bool FileHandler::saveDoubleListToFile(const DoubleList<int>& list, const std::string& filename) {
    // const DoubleList& - lista jest przekazywana przez referencję - nie tworzymy kopii listy
    // const - funkcja nie może jej zmieniać
    std::ofstream file(filename);    // std::ofstream - zapis danych do pliku

    // jeśli nie udało się otworzyć pliku, zwracamy false
    if (!file) {
        return false;
    }

    file << list.getSize() << '\n';    //  zapis liczb elementów listy

    // zapis wszystkich elementów listy
    for (int i = 0; i < list.getSize(); ++i) {
        int value = 0;

        // pobieramy wartość spod danego indeksu
        if (!list.get(i, value)) {
            return false;
        }

        file << value << '\n';    // zapisujemy wartość do pliku

    }

    return true;
}

