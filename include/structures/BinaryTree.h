//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_BINARYTREE_H
#define PROJECT_BINARYTREE_H

#include <new>

// template - drzewo może przechowywać różne typy danych
template <typename T>
class BinaryTree {
private:
    struct Node {
        T value;        // wartość węzła
        Node* left;     // lewe dziecko
        Node* right;    // prawe dziecko

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
        if (index < 0 || index >= size) {
            return nullptr;
        }

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

        // cofamy się o dwa bity:
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
    const Node* getNode(int index) const {
        if (index < 0 || index >= size) {
            return nullptr;
        }

        if (index == 0) {
            return root;
        }

        const Node* current = root;
        int path = index + 1;

        int mask = 1;
        while (mask <= path) {
            mask <<= 1;
        }

        mask >>= 2;

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

    // usuwa wszystkie węzły drzewa
    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
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
        int parentIndex = (newIndex - 1) / 2;

        Node* parent = getNode(parentIndex);

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

        if (node == nullptr) {
            return false;
        }

        value = node->value;
        return true;
    }

    // ustawia nową wartość pod indeksem
    bool set(int index, const T& value) {
        Node* node = getNode(index);

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