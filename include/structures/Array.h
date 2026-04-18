//
// Created by MariiaHuzhva on 22/03/2026.
//

#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H

#include <new>

// template - klasa będzie działała dla różnych typów danych
// typename T - T zostanie później zastąpione prawdziwym typem
// na przykład int, double albo std::string
template <typename T>
class Array {
private:
    T* data;   // wskaźnik na dynamiczną tablicę elementów typu T
    // T* oznacza adres pierwszego elementu tablicy w pamięci dynamicznej

    int size;  // liczba elementów tablicy

public:
    // konstruktor tworzy tablicę o zadanym rozmiarze
    explicit Array(int s)  {
        data = nullptr;     // data - nullptr - tablica jeszcze nie wskazuje na żadne dane
        size =0;    //bo  tablica jest pusta

        // jeśli rozmiar jest 0 albo < - nie tworzymy tablicy
        if (s <= 0) {
            return;
        }
        // tworzymy dynamiczną tablicę z s elementami typu T
        // std::nothrow - przy braku pamięci dostaniemy nullptr zamiast wyjątku

        data = new (std::nothrow) T[s];
        if (data != nullptr) {
            size = s;
        }        // jeśli pamięć została poprawnie przydzielona - zapisujemy prawdziwy rozmiar tablicy
    }

    // destruktor zwalnia pamięć zajętą przez tablicę
    ~Array() {
        delete[] data;
        // delete[] usuwa całą tablicę utworzoną przez new[]
    }

    // zwraca aktualny rozmiar tablicy
    int getSize() const {
        return size;
    }

    // sprawdza, czy tablica jest pusta
    bool empty() const {
        return size == 0;
    }

    // zwraca referencję do elementu pod danym indeksem
    T& setId(int index) {
        // T& oznacza referencję, czyli dostęp do prawdziwego elementu tablicy
        // dzięki temu można ten element odczytać albo zmienić
        return data[index];
    }

    // wersja const - dla obiektów stałych
    const T& setId(int index) const {
        // const T& oznacza referencję tylko do odczytu
        // tej wersji używamy, gdy obiekt Array jest stały
        return data[index];
    }

    // blokujemy kopiowanie tablicy
    // dzięki temu nie powstaną dwie tablice ze wskaźnikiem do tej samej pamięci
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    // odczytuje wartość spod indeksu
    bool get(int index, T& value) const {
        if (index < 0 || index >= size) {    // jeśli indeks jest poza zakresem, nie można odczytać elementu
            return false;
        }

        value = data[index];    // zapisujemy znalezioną wartość do zmiennej przekazanej przez referencję
        return true;
    }

    // ustawia nową wartość pod danym indeksem
    bool set(int index, const T& value) {
        // const T& - wartość przekazujemy bez kopiowania
        // const - tej wartości nie zmieniamy w funkcji

        // jeśli indeks jest poza zakresem, zmiana nie jest możliwa
        if (index < 0 || index >= size) {
            return false;
        }

        data[index] = value;    // wpisujemy nową wartość do tablicy
        return true;
    }

    // czyści tablicę
    void clear() {
        delete[] data;    // zwalniamy pamięć zajętą przez elementy
        data = nullptr;    // po usunięciu tablica nie wskazuje już na żadne dane
        size = 0;    // rozmiar ustawiamy na 0, bo tablica jest pusta

    }
};

#endif // PROJECT_ARRAY_H