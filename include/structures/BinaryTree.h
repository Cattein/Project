//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_BINARYTREE_H
#define PROJECT_BINARYTREE_H

#include <new>

// template - drzewo może przechowywać różne typy danych
// elementy są dodawane poziomami, jak w pełnym drzewie binarnym
template <typename T>
class BinaryTree {
private:
    // pojedynczy węzeł drzewa
    struct Node {
        T value;        // wartość przechowywana w węźle
        Node* left;     // wskaźnik na lewe dziecko
        Node* right;    // wskaźnik na prawe dziecko

        // tworzy nowy węzeł z podaną wartością
        explicit Node(const T& newValue) : value(newValue), left(nullptr), right(nullptr) {}
    };

    Node* root;   // korzeń drzewa
    int size;     // liczba elementów w drzewie

    // zwraca wskaźnik do węzła o podanym indeksie
    // indeksy są liczone poziomami:
    // 0 - root
    // 1 - lewe dziecko root
    // 2 - prawe dziecko root
    // 3 - lewe dziecko węzła 1 itd.
    Node* getNode(int index) {
        // jeśli indeks jest poza zakresem, nie da się znaleźć węzła
        if (index < 0 || index >= size) {
            return nullptr;
        }

        // indeks 0 zawsze oznacza korzeń
        if (index == 0) {
            return root;
        }

        Node* current = root;

        // zamieniamy indeks na numer pozycji od 1
        // dzięki temu łatwo wyznaczyć drogę od korzenia
        int path = index + 1;

        // szukamy najwyższej potęgi 2 nie większej od path
        int mask = 1;
        while (mask <= path) {
            mask <<= 1;
        }

        // cofamy się o dwa bity
        // najwyższy bit oznacza sam korzeń, więc go pomijamy
        mask >>= 2;

        // przechodzimy po kolejnych bitach:
        // 0 - idziemy w lewo
        // 1 - idziemy w prawo
        while (mask > 0 && current != nullptr) {
            if ((path & mask) == 0) {
                current = current->left;
            } else {
                current = current->right;
            }

            mask >>= 1;
        }

        return current;
    }

    // wersja const
    // działa tak samo jak poprzednia, ale nie pozwala zmieniać danych w węźle
    const Node* getNode(int index) const {
        // jeśli indeks jest poza zakresem, zwracamy nullptr
        if (index < 0 || index >= size) {
            return nullptr;
        }

        // indeks 0 oznacza korzeń
        if (index == 0) {
            return root;
        }

        const Node* current = root;
        int path = index + 1;

        // wyznaczamy najwyższą potęgę 2 nie większą od path
        int mask = 1;
        while (mask <= path) {
            mask <<= 1;
        }

        // pomijamy bit odpowiadający korzeniowi
        mask >>= 2;

        // odczytujemy drogę do szukanego węzła z kolejnych bitów
        while (mask > 0 && current != nullptr) {
            if ((path & mask) == 0) {
                current = current->left;
            } else {
                current = current->right;
            }

            mask >>= 1;
        }

        return current;
    }

    // usuwa wszystkie węzły zaczynając od podanego poddrzewa
    void clear(Node* node) {
        // jeśli węzeł nie istnieje, nie ma czego usuwać
        if (node == nullptr) {
            return;
        }

        // najpierw usuwamy lewe i prawe poddrzewo
        clear(node->left);
        clear(node->right);

        // na końcu usuwamy bieżący węzeł
        delete node;
    }

public:
    // tworzy puste drzewo
    BinaryTree() : root(nullptr), size(0) {}

    // destruktor usuwa całe drzewo
    ~BinaryTree() {
        clear();
    }

    // blokujemy kopiowanie
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    // zwraca liczbę elementów
    int getSize() const {
        return size;
    }

    // sprawdza, czy drzewo jest puste
    bool empty() const {
        return size == 0;
    }

    // dodaje nowy element na koniec drzewa
    // pozycja jest wyznaczana tak, żeby drzewo było wypełniane poziomami
    bool pushBack(const T& value) {
        Node* newNode = new (std::nothrow) Node(value);

        // jeśli nie udało się utworzyć nowego węzła, zwracamy false
        if (newNode == nullptr) {
            return false;
        }

        // jeśli drzewo było puste, nowy węzeł staje się korzeniem
        if (root == nullptr) {
            root = newNode;
            ++size;
            return true;
        }

        // indeks nowego elementu będzie równy obecnemu size
        int newIndex = size;

        // rodzic nowego elementu w numeracji poziomami
        int parentIndex = (newIndex - 1) / 2;

        Node* parent = getNode(parentIndex);

        // jeśli nie udało się znaleźć rodzica, trzeba zwolnić pamięć
        if (parent == nullptr) {
            delete newNode;
            return false;
        }

        // jeśli indeks nowego elementu jest nieparzysty -> lewe dziecko
        // jeśli parzysty -> prawe dziecko
        if (newIndex % 2 == 1) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        ++size;
        return true;
    }

    // odczytuje wartość spod indeksu
    bool get(int index, T& value) const {
        const Node* node = getNode(index);

        // jeśli węzeł nie istnieje, odczyt się nie udał
        if (node == nullptr) {
            return false;
        }

        value = node->value;
        return true;
    }

    // ustawia nową wartość pod indeksem
    bool set(int index, const T& value) {
        Node* node = getNode(index);

        // jeśli węzeł nie istnieje, zapis się nie udał
        if (node == nullptr) {
            return false;
        }

        node->value = value;
        return true;
    }

    // usuwa całe drzewo
    void clear() {
        clear(root);
        root = nullptr;
        size = 0;
    }
};

#endif // PROJECT_BINARYTREE_H