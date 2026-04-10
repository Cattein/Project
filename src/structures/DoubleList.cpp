//
// Created by MashaGuzhva on 04/04/2026.
//
#include "structures/DoubleList.h"
#include <new>
// Potrzebne do std::nothrow.


// Tworzy nowy element listy z podaną wartością, nie ma sasiadow.
DoubleList::Node::Node(int newValue) : value(newValue), prev(nullptr), next(nullptr){}

// Pusta lista.
DoubleList::DoubleList() : head(nullptr), tail(nullptr), size(0){}

// Destruktor listy
DoubleList::~DoubleList(){
    clear();
}

// Zwracanie liczbe elementow.
int DoubleList::getSize() const{
    return size;
}

// if size == 0, lista jest pusta.
bool DoubleList::empty() const{
    return size == 0;
}

// zwraca wskaźnik do węzła o podanym indeksie,  wersja działa dla zwykłego obiektu listy, więc pozwala później modyfikować węzeł
DoubleList::Node* DoubleList::getNode(int index){
    if (index < 0 || index >= size) {// if indeks jest poza zakresem,
        return nullptr;
    }

    Node* current = head;    // zaczynamy od poczatku

    for (int i = 0; i < index; ++i) {
        current = current->next;
    }    // szukanego indeksu

    return current;    // znaleziony wezel
}
// zwraca wskaźnik do węzła o podanym indeksie. wersja const, gdy lista jest stała i nie wolno zmieniać jej zawartości
const DoubleList::Node* DoubleList::getNode(int index) const{
    if (index < 0 || index >= size) {
        return nullptr;
    }    // zakres indeksu.

    const Node* current = head;    // Zaczynamy od poczatku.

    for (int i = 0; i < index; ++i) {
        current = current->next;
    } // Idziemy do szukanego indeksu.

    return current;// Zwracamy znaleziony wezel.
}

// dodaje nowy element na początek listy
bool DoubleList::pushFront(int value){
    Node* newNode = new (std::nothrow) Node(value); // tworzy nowy węzeł, std::nothrow - w razie braku pamięci dostaniemy nullptr, zamiast przerwania programu wyjątkiem

    if (newNode == nullptr) {
        return false;
    }// if brak pamieci -> false

    newNode->next = head; // nowy wezel wskazuje na stary poczatek, jego next wskazuje na stary head

    if (head != nullptr) {
        head->prev = newNode;
    }// if lista nie byla pusta, stary head dostaje poprzednika

    head = newNode;// nowy wezel staje sie poczatkiem

    if (tail == nullptr) {
        tail = newNode;
    }// if lista byla pusta, ten sam element jest tez koncem

    ++size;
    return true;
}

// dodaje nowy element na koniec listy
bool DoubleList::pushBack(int value){
    Node* newNode = new (std::nothrow) Node(value);
    // tworzy nowy węzeł, jeśli zabraknie pamięci, dostaniemy nullptr zamiast wyjątku

    if (newNode == nullptr) {
        return false;
    }// if brak pamieci, zwracamy false.

    newNode->prev = tail; // nowy element będzie za obecnym końcem, więc jego prev wskazuje na stary tail

    if (tail != nullptr) {
        tail->next = newNode;
    }// if lista nie byla pusta, stary tail wskazuje na nowy element.

    tail = newNode;// Nowy wezel staje sie nowym koncem.

    if (head == nullptr) {
        head = newNode;
    }// if lista byla pusta, ten sam element jest tez poczatkiem.

    ++size;
    return true;
}
// odczytuje wartość elementu o podanym indeksie i zapisuje ją do zmiennej przekazanej przez referencję
bool DoubleList::get(int index, int& value) const{
    const Node* node = getNode(index);// szukanie wezla

    if (node == nullptr) {
        return false;
    }// if indeks jest zly, zwracamy false.

    value = node->value; // przepisujemy wartość z węzła do zmiennej wyjściowej
    return true;
}

// zmienia wartość elementu o podanym indeksie
bool DoubleList::set(int index, int value){
    Node* node = getNode(index);// szukamy węzła, który chcemy zmodyfikować

    if (node == nullptr) {
        return false;
    }// if indeks jest zly, zwracamy false.

    node->value = value;// nadpisujemy starą wartość nową
    return true;
}

// usuwa wszystkie elementy z listy
void DoubleList::clear(){
    Node* current = head;// zaczynamy od poczatku.

    while (current != nullptr) {
        Node* nextNode = current->next;     // Zapamietujemy nastepny element.
        delete current; // Usuwamy biezacy element.
        current = nextNode; // Przechodzimy dalej.
    }

    head = nullptr;     // Lista nie ma juz poczatku.
    tail = nullptr;     // Lista nie ma juz konca.
    size = 0;            // Lista jest pusta.
}