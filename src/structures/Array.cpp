//
// Created by MashaGuzhva on 22/03/2026.
//

#include "structures/Array.h"

// zapisuje rozmiar i tworzy dynamiczną tablicę
Array::Array(int s) {
    size = s;
    if (size > 0) {    // jeśli rozmiar jest większy od zera, tworzymy tablicę w pamięci dynamicznej
        data = new int[size];
    } else {
        // dla pustej tablicy ustawiamy wskaźnik na nullptr
        data = nullptr;
    }
}

// destruktor zwalnia pamięć zajętą przez tablicę
Array::~Array() {
    delete[] data;
}

// odczytuje wartość spod podanego indeksu
bool Array::get(int index, int& value) const {
    if (index < 0 || index >= size) {    // jeśli indeks jest poza zakresem, nie można odczytać elementu
        return false;
    }

    value = data[index];    // zapisujemy znalezioną wartość do zmiennej przekazanej przez referencję
    return true;
}

// ustawia nową wartość pod podanym indeksem
bool Array::set(int index, int value) {
    // jeśli indeks jest poza zakresem, zmiana nie jest możliwa
    if (index < 0 || index >= size) {
        return false;
    }

    data[index] = value;    // wpisujemy nową wartość do tablicy
    return true;
}

// czyści tablicę i ustawia ją jako pustą
void Array::clear() {
    delete[] data;    // zwalniamy pamięć zajętą przez elementy
    data = nullptr;    // po usunięciu tablica nie wskazuje już na żadne dane
    size = 0;    // rozmiar ustawiamy na 0, bo tablica jest pusta

}