#ifndef PROJECT_SINGLELIST_H
#define PROJECT_SINGLELIST_H

#include <new>

// template -  lista mo przechowywać różne typy danych
// T będzie później zastąpione prawdziwym typem, np int, double albo string
template <typename T>
class SingleList {
private:
    struct Node {
        T value;      // wartość elementu
        Node* next;   // wskaźnik na następny element listy
        // Node* - adres następnego węzła
        // jeśli next == nullptr -  ostatni element

        // const T& -  wartość przekazujemy bez kopiowania
        // explicit chroni przed przypadkową zamianą typu T na Node
        explicit Node(const T& newValue) : value(newValue), next(nullptr) {}
    };

    Node* head;   // pierwszy element listy
    Node* tail;   // ostatni element listy
    int size;     // liczba elementów

    // zwraca wskaźnik do węzła o podanym indeksie
    Node* getNode(int index) {
        if (index < 0 || index >= size) {
            return nullptr;
        }
        // jeśli indeks jest poza zakresem, zwracamy pusty wskaźnik

        Node* current = head;   // start od pierwszego elementu
        // current będzie przesuwał się po liście

        for (int i = 0; i < index; ++i) {
            current = current->next;
        } // przechodzimy po liscie do szukanego indeksu

        return current;     // zwracamy znaleziony wezel
    }

    // wersja const
    // działa dla stałej listy i nie pozwala zmieniać węzła
    const Node* getNode(int index) const {
        if (index < 0 || index >= size) {
            return nullptr;
        }

        const Node* current = head;    // start od poczatku listy
        // const Node* - wskaźnik do stałego węzła
        // przez taki wskaźnik nie można zmieniać wartości węzła

        for (int i = 0; i < index; ++i) {    // idziemy do odpowiedniego wezla
            current = current->next;
        }

        return current; // zwracamy wskaznik do stalego wezla
    }

public:
    // tworzy pustą listę
    SingleList() : head(nullptr), tail(nullptr), size(0) {}
    // na początku lista nie ma elementów, więc head i tail są puste

    // destruktor usuwa wszystkie elementy
    ~SingleList() {
        clear();
    }
    // destruktor wywołuje clear, by nie było wycieków pamięci

    // blokujemy kopiowanie listy
    // dzięki temu nie powstaną przypadkowe kopie ze wskaźnikami do tych samych danych
    SingleList(const SingleList&) = delete;
    SingleList& operator=(const SingleList&) = delete;

    int getSize() const {
        return size;
    }
    // zwraca aktualną liczbę elementów

    bool empty() const {
        return size == 0;
    }
    // sprawdza, czy lista jest pusta

    // dodaje element na początek listy
    bool pushFront(const T& value) {
        Node* newNode = new (std::nothrow) Node(value); // nowy wezel
        // nothrow powoduje, ze przy braku pamieci dostaniemy nullptr
        // new tworzy obiekt w pamięci dynamicznej

        if (newNode == nullptr) {
            return false;
        } // if not create - false

        newNode->next = head;      // nowy wezel ma wskazywac na stary poczatek listy
        head = newNode;     // nowy staje sie nowym poczatkiem

        if (tail == nullptr) {
            tail = newNode;
        } // jesli lista byla pusta, ten sam element jest tez koncem

        ++size;
        // zwiększamy liczbę elementów listy

        return true;
    }

    // dodaje element na koniec listy
    bool pushBack(const T& value) {
        Node* newNode = new (std::nothrow) Node(value); // add nowy wezel na koniec listy

        if (newNode == nullptr) {
            return false;
        } // brak pamieci = blad

        if (tail == nullptr) { // if lista byla pusta, nowy element jest pierwszy i ostatni
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        } // w przeciwnym razie dopinamy go za tail i przesuwamy tail

        ++size; // +1 do liczbe elementow

        return true;
    }

    // odczytuje wartość spod indeksu
    bool get(int index, T& value) const {
        const Node* node = getNode(index); // pobieramy wezel spod podanego indeksu

        if (node == nullptr) {
            return false;
        } // jesli indeks byl zly -> false

        value = node->value; // przepisujemy wartosc do zmiennej podanej przez uzytkownika
        return true;
    }

    // ustawia nową wartość pod indeksem
    bool set(int index, const T& value) {
        Node* node = getNode(index);    // szukamy wezla, ktory chcemy zmienic

        if (node == nullptr) {
            return false;
        } // jesli indeks jest niepoprawny, nic nie zmieniamy

        node->value = value; // stara wartosc -> na nowa
        return true;
    }

    // usuwa całą listę
    void clear() {
        Node* current = head;   // usuwanie od pierwszego elementu

        while (current != nullptr) {
            Node* nextNode = current->next;     // zapamietujemy adres nastepnego elementu -> usuniemy biezacy
            delete current;          // usuwamy aktualny wezel i zwalniamy pamiec
            current = nextNode;     // przechodzimy do kolejnego wezla
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
        // po clear lista jest znowu pusta
    }
};

#endif // PROJECT_SINGLELIST_H