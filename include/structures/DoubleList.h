//
// Created by MashaGuzhva on 04/04/2026.
//

#ifndef PROJECT_DOUBLELIST_H
#define PROJECT_DOUBLELIST_H

class DoubleList {
private:
    struct Node {
        int value;  // Wartosc elementu.
        Node* prev; // Wskaznik na poprzedni element.
        Node* next; // Wskaznik na nastepny element.
        explicit Node(int newValue);    // tworzy nowy wezel.
    };

    Node* head; // 1 element listy
    Node* tail; // ostatni element listy

    int size;
    Node* getNode(int index); // zwraca wezel o podanym indeksie
    const Node* getNode(int index) const;

public:
    DoubleList(); // pusta liste
    ~DoubleList(); // usuwa wszystkie elementy
    DoubleList(const DoubleList&) = delete;// Blok kopiowania
    DoubleList& operator=(const DoubleList&) = delete; // Blok przypisania

    int getSize() const;    // Zwraca liczbe elementow
    bool empty() const;     //  czy lista jest pusta
    bool pushFront(int value);  // add element na poczatek
    bool pushBack(int value);   // add element na koniec
    bool get(int index, int& value) const;  //odczytuje wartosc spod indeksu.
    bool set(int index, int value); //ustawia wartosc pod indeksem.
    void clear(); //usuwa cala liste.
};

#endif //PROJECT_DOUBLELIST_H