//
// Created by MashaGuzhva on 18/04/2026.
//

#ifndef PROJECT_STACK_H
#define PROJECT_STACK_H

#include <new>

// template - stos może przechowywać różne typy danych
template <typename T>
class Stack {
private:
    // pojedynczy element stosu
    struct Node {
        T value;      // przechowywana wartość
        Node* next;   // wskaźnik na następny element

        // tworzy nowy węzeł z podaną wartością
        explicit Node(const T& newValue) : value(newValue), next(nullptr) {}
    };

    Node* topNode;    // wskaźnik na element znajdujący się na szczycie stosu
    int size;         // aktualna liczba elementów w stosie

    // zwraca wskaźnik do węzła o podanym indeksie
    // indeks 0 oznacza element ze szczytu stosu
    Node* getNode(int index) {
        // jeśli indeks jest niepoprawny, zwracamy nullptr
        if (index < 0 || index >= size) {
            return nullptr;
        }

        Node* current = topNode;
        // zaczynamy od szczytu stosu

        // przechodzimy do kolejnych elementów aż do podanego indeksu
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        return current;
    }

    // wersja const tej samej funkcji
    // używana wtedy, gdy stos nie może być modyfikowany
    const Node* getNode(int index) const {
        // jeśli indeks jest niepoprawny, zwracamy nullptr
        if (index < 0 || index >= size) {
            return nullptr;
        }

        const Node* current = topNode;
        // zaczynamy od szczytu stosu

        // przechodzimy dalej aż do szukanego indeksu
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        return current;
    }

public:
    // tworzy pusty stos
    Stack() : topNode(nullptr), size(0) {}

    // destruktor usuwa wszystkie elementy stosu
    ~Stack() {
        clear();
    }

    // blokuje kopiowanie stosu
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    // zwraca aktualną liczbę elementów
    int getSize() const {
        return size;
    }

    // sprawdza, czy stos jest pusty
    bool empty() const {
        return size == 0;
    }

    // dodaje nowy element na szczyt stosu
    bool push(const T& value) {
        Node* newNode = new (std::nothrow) Node(value);

        // jeśli nie udało się przydzielić pamięci, zwracamy false
        if (newNode == nullptr) {
            return false;
        }

        // nowy element wskazuje na poprzedni szczyt
        newNode->next = topNode;

        // nowy element staje się nowym szczytem stosu
        topNode = newNode;
        ++size;

        return true;
    }

    // usuwa element ze szczytu stosu i zapisuje jego wartość do value
    bool pop(T& value) {
        // jeśli stos jest pusty, nie można nic usunąć
        if (topNode == nullptr) {
            return false;
        }

        // zapamiętujemy stary szczyt
        Node* nodeToDelete = topNode;

        // odczytujemy wartość ze szczytu
        value = nodeToDelete->value;

        // przesuwamy szczyt na kolejny element
        topNode = topNode->next;

        // usuwamy stary węzeł
        delete nodeToDelete;
        --size;

        return true;
    }

    // odczytuje wartość ze szczytu stosu bez usuwania elementu
    bool top(T& value) const {
        // jeśli stos jest pusty, nie ma czego odczytać
        if (topNode == nullptr) {
            return false;
        }

        value = topNode->value;
        return true;
    }

    // odczytuje wartość elementu pod podanym indeksem
    // indeks 0 oznacza szczyt stosu
    // ta metoda jest używana pomocniczo, np. przy sortowaniu i kopiowaniu
    bool get(int index, T& value) const {
        const Node* node = getNode(index);

        // jeśli indeks jest niepoprawny, zwracamy false
        if (node == nullptr) {
            return false;
        }

        value = node->value;
        return true;
    }

    // ustawia nową wartość elementu pod podanym indeksem
    // podobnie jak get, metoda jest pomocnicza
    bool set(int index, const T& value) {
        Node* node = getNode(index);

        // jeśli indeks jest niepoprawny, zwracamy false
        if (node == nullptr) {
            return false;
        }

        node->value = value;
        return true;
    }

    // usuwa wszystkie elementy stosu
    void clear() {
        Node* current = topNode;
        // zaczynamy od szczytu

        // przechodzimy po wszystkich elementach i usuwamy je po kolei
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        // po wyczyszczeniu stos jest pusty
        topNode = nullptr;
        size = 0;
    }
};

#endif // PROJECT_STACK_H