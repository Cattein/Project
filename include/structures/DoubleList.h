//
// Created by MashaGuzhva on 04/04/2026.
//

#ifndef PROJECT_DOUBLELIST_H
#define PROJECT_DOUBLELIST_H

#include <new>

// template oznacza, że lista może przechowywać różne typy danych
template <typename T>
class DoubleList {
private:
    struct Node {
        T value;       // wartość elementu
        Node* prev;    // wskaźnik na poprzedni element
        Node* next;    // wskaźnik na następny element

        // tworzy nowy element listy z podaną wartością, nie ma sasiadow
        explicit Node(const T& newValue) : value(newValue), prev(nullptr), next(nullptr) {}
    };

    Node* head;   // pierwszy element listy
    Node* tail;   // ostatni element listy
    int size;     // liczba elementów

    // zwraca wskaźnik do węzła o podanym indeksie, wersja działa dla zwykłego obiektu listy, więc pozwala później modyfikować węzeł
    Node* getNode(int index) {
        if (index < 0 || index >= size) { // if indeks jest poza zakresem
            return nullptr;
        }

        Node* current = head;    // zaczynamy od poczatku

        for (int i = 0; i < index; ++i) {
            current = current->next;
        }    // szukanego indeksu

        return current;    // znaleziony wezel
    }

    // zwraca wskaźnik do węzła o podanym indeksie, wersja const, gdy lista jest stała i nie wolno zmieniać jej zawartości
    const Node* getNode(int index) const {
        if (index < 0 || index >= size) {
            return nullptr;
        }    // zakres indeksu

        const Node* current = head;    // zaczynamy od poczatku

        for (int i = 0; i < index; ++i) {
            current = current->next;
        } // idziemy do szukanego indeksu

        return current; // zwracamy znaleziony wezel
    }

public:
    // pusta lista
    DoubleList() : head(nullptr), tail(nullptr), size(0) {}

    // destruktor listy
    ~DoubleList() {
        clear();
    }

    DoubleList(const DoubleList&) = delete;
    DoubleList& operator=(const DoubleList&) = delete;

    // zwracanie liczbe elementow
    int getSize() const {
        return size;
    }

    // if size == 0, lista jest pusta
    bool empty() const {
        return size == 0;
    }

    // dodaje nowy element na początek listy
    bool pushFront(const T& value) {
        Node* newNode = new (std::nothrow) Node(value);
        // tworzy nowy węzeł, std::nothrow - w razie braku pamięci dostaniemy nullptr, zamiast przerwania programu wyjątkiem

        if (newNode == nullptr) {
            return false;
        } // if brak pamieci -> false

        newNode->next = head; // nowy wezel wskazuje na stary poczatek, jego next wskazuje na stary head

        if (head != nullptr) {
            head->prev = newNode;
        } // if lista nie byla pusta, stary head dostaje poprzednika

        head = newNode; // nowy wezel staje sie poczatkiem

        if (tail == nullptr) {
            tail = newNode;
        } // if lista byla pusta, ten sam element jest tez koncem

        ++size;
        return true;
    }

    // dodaje nowy element na koniec listy
    bool pushBack(const T& value) {
        Node* newNode = new (std::nothrow) Node(value);
        // tworzy nowy węzeł, jeśli zabraknie pamięci, dostaniemy nullptr zamiast wyjątku

        if (newNode == nullptr) {
            return false;
        } // if brak pamieci, zwracamy false

        newNode->prev = tail; // nowy element będzie za obecnym końcem, więc jego prev wskazuje na stary tail

        if (tail != nullptr) {
            tail->next = newNode;
        } // if lista nie byla pusta, stary tail wskazuje na nowy element

        tail = newNode; // nowy wezel staje sie nowym koncem

        if (head == nullptr) {
            head = newNode;
        } // if lista byla pusta, ten sam element jest tez poczatkiem

        ++size;
        return true;
    }

    // odczytuje wartość elementu o podanym indeksie i zapisuje ją do zmiennej przekazanej przez referencję
    bool get(int index, T& value) const {
        const Node* node = getNode(index); // szukanie wezla

        if (node == nullptr) {
            return false;
        } // if indeks jest zly, zwracamy false

        value = node->value; // przepisujemy wartość z węzła do zmiennej wyjściowej
        return true;
    }

    // zmienia wartość elementu o podanym indeksie
    bool set(int index, const T& value) {
        Node* node = getNode(index); // szukamy węzła, który chcemy zmodyfikować

        if (node == nullptr) {
            return false;
        } // if indeks jest zly, zwracamy false

        node->value = value; // nadpisujemy starą wartość nową
        return true;
    }

    // usuwa wszystkie elementy z listy
    void clear() {
        Node* current = head; // zaczynamy od poczatku

        while (current != nullptr) {
            Node* nextNode = current->next;     // zapamietujemy nastepny element
            delete current; // usuwamy biezacy element
            current = nextNode; // przechodzimy dalej
        }

        head = nullptr;     // lista nie ma juz poczatku
        tail = nullptr;     // lista nie ma juz konca
        size = 0;           // lista jest pusta
    }
};

#endif // PROJECT_DOUBLELIST_H