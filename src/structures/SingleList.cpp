#include "structures/SingleList.h"
#include <new> // std::nothrow

// set wartosc wezla, next = nullptr, bo nowy wezel teraz nie ma nastepnego
SingleList::Node::Node(int newValue) : value(newValue), next(nullptr) {}

// pusta lista  - nie ma 1, ostatniego elementu, rozmiar 0
SingleList::SingleList() : head(nullptr), tail(nullptr), size(0){}

// przy usuwaniu obiektu czyscimy cala liste
SingleList::~SingleList() {
    clear();
}

// rozmiar listy
int SingleList::getSize() const{
    return size;
}

bool SingleList::empty() const{
    return size == 0; // if size = 0 - lista jest pusta
}

// czy indeks jest poprawny, gdy jest zly, zwracamy nullptr
SingleList::Node* SingleList::getNode(int index){
    if (index < 0 || index >= size) {
        return nullptr;
    }

    Node* current = head;   // start od pierwszego elementu

    for (int i = 0; i < index; ++i) {
        current = current->next;
    }// Przechodzimy po liscie do szukanego indeksu

    return current;     // Zwracamy znaleziony wezel
}

const SingleList::Node* SingleList::getNode(int index) const{
    if (index < 0 || index >= size) {
        return nullptr;}

    const Node* current = head;    // start od poczatku listy

    for (int i = 0; i < index; ++i) {    // idziemy do odpowiedniego wezla

        current = current->next;
    }

    return current; // zwracamy wskaznik do stalego wezla
}

bool SingleList::pushFront(int value)
{
    Node* newNode = new (std::nothrow) Node(value); // nowy wezel
    // nothrow powoduje, ze przy braku pamieci dostaniemy nullptr

    if (newNode == nullptr) {
        return false;
    }// if not create - false

    newNode->next = head;      // nowy wezel ma wskazywac na stary poczatek listy
    head = newNode;     //  nowy staje sie nowym poczatkiem

    if (tail == nullptr) {
        tail = newNode;
    }   // Jesli lista byla pusta, ten sam element jest tez koncem

    ++size;
    return true;
}

bool SingleList::pushBack(int value)
{
    Node* newNode = new (std::nothrow) Node(value);//add nowy wezel na koniec listy
    if (newNode == nullptr) {
        return false;
    }// brak pamieci = blad.

    if (tail == nullptr) {// if lista byla pusta, nowy element jest pierwszy i ostatni

        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }//w przeciwnym razie dopinamy go za tail i przesuwamy tail

    ++size;// +1 do liczbe elementow.

    return true;
}

bool SingleList::get(int index, int& value) const
{
    const Node* node = getNode(index);// Pobieramy wezel spod podanego indeksu.
    if (node == nullptr) {
        return false;
    }// Jesli indeks byl zly -> false

    value = node->value; // Przepisujemy wartosc do zmiennej podanej przez uzytkownika.
    return true;
}

bool SingleList::set(int index, int value)
{
    Node* node = getNode(index);    // szukamy wezla, ktory chcemy zmienic
    if (node == nullptr) {
        return false;
    }// Jesli indeks jest niepoprawny, nic nie zmieniamy

    node->value = value; // stara wartosc -> na nowa
    return true;
}

void SingleList::clear()
{
    Node* current = head;   // usuwanie od pierwszego elementu.
    while (current != nullptr) {
        Node* nextNode = current->next;     // zapamietujemy adres nastepnego elementu -> usuniemy biezacy
        delete current;          // Usuwamy aktualny wezel i zwalniamy pamiec.
        current = nextNode;     // Przechodzimy do kolejnego wezla.
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}