#ifndef PROJECT_SINGLELIST_H
#define PROJECT_SINGLELIST_H
// Chroni przed wielokrotnym dolaczeniem tego pliku

class SingleList {
private:
    struct Node {   // 1 element listy.
        int value;  // wartosc elementu
        Node* next; //  nastepny element listy
        explicit Node(int newValue);    // nowy wezel z podana wartoscia.
    };

    Node* head;     // Wskaznik na 1 element listy
    Node* tail;     // Wskaznik na ostatni element listy
    int size;       // Liczba elementow w liscie

    Node* getNode(int index);   // Zwraca wezel o podanym indeksie - do uzytku wewnatrz klasy
    const Node* getNode(int index) const;   // To samo co wyzej, ale dla obiektu const.

public:
    SingleList();   // Tworzy pusta liste
    ~SingleList();      // Usuwa wszystkie elementy i zwalnia pamiec

    SingleList(const SingleList&) = delete; // Blokuje kopiowanie, aby nie bylo problemow z pamiecia
    SingleList& operator=(const SingleList&) = delete;// Blokuje przypisanie z tego samego powodu

    int getSize() const; // Zwraca liczbe elementow

    bool empty() const;     // Sprawdza, czy lista jest pusta

    bool pushFront(int value);  // Dodaje element na poczatek listy

    bool pushBack(int value);   // Dodaje element na koniec listy

    bool get(int index, int& value) const;  // Odczytuje wartosc spod indeksu. Jesli indeks jest nie poprawny -  false.

    bool set(int index, int value); // Ustawia nowa wartosc pod indeksem. Jesli indeks jest zly, zwraca false

    void clear(); // Usuwa liste
};

#endif // PROJECT_SINGLELIST_H