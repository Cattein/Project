//
// Created by MashaGuzhva on 11/04/2026.
//

#include "algorytmsSorting/BucketSort.h"
#include <new>

// anonymous namespace
// wszystko zapisane tutaj jest widoczne tylko w tym pliku
namespace {

    // prosty węzeł listy jednokierunkowej
    // każdy kubełek przechowujemy jako osobną listę
    struct Node {
        int value;    // wartość zapisana w kubełku
        Node* next;   // wskaźnik na następny element listy

        // tworzy nowy węzeł z podaną wartością
        explicit Node(int newValue) : value(newValue), next(nullptr) {}
    };

    // dodaje nowy element na koniec listy kubełka
    // head - początek listy
    // tail - koniec listy
    bool pushBack(Node*& head, Node*& tail, int value) {
        Node* newNode = new (std::nothrow) Node(value);

        // jeśli nie udało się przydzielić pamięci, zwracamy false
        if (newNode == nullptr) {
            return false;
        }

        // jeśli lista była pusta, nowy element jest jednocześnie początkiem i końcem
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            // w przeciwnym razie dopinamy nowy element na koniec
            tail->next = newNode;
            tail = newNode;
        }

        return true;
    }

    // sortuje pojedynczy kubełek za pomocą insertion sorta
    // ponieważ każdy kubełek jest listą jednokierunkową,
    // taki sposób sortowania jest prosty do zaimplementowania
    void insertionSortList(Node*& head) {
        // pusta lista albo lista jednoelementowa jest już posortowana
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Node* sorted = nullptr;
        // tutaj będziemy budować nową, już posortowaną listę

        // przenosimy po kolei elementy ze starej listy do nowej
        while (head != nullptr) {
            Node* current = head;
            head = head->next;
            // odłączamy pierwszy element ze starej listy

            // jeśli lista wynikowa jest pusta albo current powinien być na początku
            if (sorted == nullptr || current->value < sorted->value) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;

                // szukamy miejsca, za którym trzeba wstawić current
                while (temp->next != nullptr && temp->next->value <= current->value) {
                    temp = temp->next;
                }

                current->next = temp->next;
                temp->next = current;
            }
        }


        head = sorted; // po zakończeniu head ma wskazywać na posortowaną listę
    }

    // usuwa wszystkie listy w kubełkach
    // na końcu usuwa też tablicę wskaźników heads
    void clearBuckets(Node** heads, int bucketCount) {
        // przechodzimy po każdym kubełku osobno
        for (int i = 0; i < bucketCount; ++i) {
            Node* current = heads[i];

            // usuwamy całą listę w danym kubełku
            while (current != nullptr) {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        delete[] heads;
    }

    // ===== odczyt i zapis dla Array =====

    // odczytuje wartość spod indeksu z tablicy
    int readAt(const Array<int>& array, int index) {
        return array.setId(index);
    }

    // zapisuje wartość pod danym indeksem w tablicy
    void writeAt(Array<int>& array, int index, int value) {
        array.setId(index) = value;
    }

    // ===== odczyt i zapis dla SingleList =====

    // odczytuje wartość spod indeksu z listy jednokierunkowej
    int readAt(const SingleList<int>& list, int index) {
        int value = 0;
        list.get(index, value);
        return value;
    }

    // zapisuje wartość pod danym indeksem w liście jednokierunkowej
    void writeAt(SingleList<int>& list, int index, int value) {
        list.set(index, value);
    }

    // ===== odczyt i zapis dla DoubleList =====

    // odczytuje wartość spod indeksu z listy dwukierunkowej
    int readAt(const DoubleList<int>& list, int index) {
        int value = 0;
        list.get(index, value);
        return value;
    }

    // zapisuje wartość pod danym indeksem w liście dwukierunkowej
    void writeAt(DoubleList<int>& list, int index, int value) {
        list.set(index, value);
    }

    // ===== wspólna implementacja BucketSort =====
    // działa dla struktur:
    // - Array<int>
    // - SingleList<int>
    // - DoubleList<int>

    template <typename Structure>
    bool bucketSortImpl(Structure& structure) {
        const int size = structure.getSize();

        // jeśli struktura jest pusta albo ma jeden element, jest już posortowana
        if (size <= 1) {
            return true;
        }

        // na początku zakładamy, że pierwszy element jest jednocześnie min i max
        int minValue = readAt(structure, 0);
        int maxValue = readAt(structure, 0);

        // szukamy prawdziwego minimum i maksimum
        for (int i = 1; i < size; ++i) {
            const int value = readAt(structure, i);

            if (value < minValue) {
                minValue = value;
            }

            if (value > maxValue) {
                maxValue = value;
            }
        }

        // jeśli wszystkie wartości są takie same, struktura jest już posortowana
        if (minValue == maxValue) {
            return true;
        }

        // liczba kubełków jest równa liczbie elementów
        const int bucketCount = size;

        // bucketHeads - początki list w kubełkach
        Node** bucketHeads = new (std::nothrow) Node*[bucketCount];

        // bucketTails - końce list w kubełkach
        Node** bucketTails = new (std::nothrow) Node*[bucketCount];

        // jeśli nie udało się utworzyć tablic kubełków, kończymy błędem
        if (bucketHeads == nullptr || bucketTails == nullptr) {
            delete[] bucketHeads;
            delete[] bucketTails;
            return false;
        }

        // na początku wszystkie kubełki są puste
        for (int i = 0; i < bucketCount; ++i) {
            bucketHeads[i] = nullptr;
            bucketTails[i] = nullptr;
        }

        // rozdzielamy elementy do kubełków
        for (int i = 0; i < size; ++i) {
            const int value = readAt(structure, i);

            // przeliczamy wartość do zakresu 0..1
            const double normalized =
                (static_cast<double>(value) - static_cast<double>(minValue)) /
                (static_cast<double>(maxValue) - static_cast<double>(minValue));

            // wyznaczamy numer kubełka
            int bucketIndex = static_cast<int>(normalized * (bucketCount - 1));

            // zabezpieczenie dolnej granicy
            if (bucketIndex < 0) {
                bucketIndex = 0;
            }

            // zabezpieczenie górnej granicy
            if (bucketIndex >= bucketCount) {
                bucketIndex = bucketCount - 1;
            }

            // dodajemy wartość do odpowiedniego kubełka
            if (!pushBack(bucketHeads[bucketIndex], bucketTails[bucketIndex], value)) {
                clearBuckets(bucketHeads, bucketCount);
                delete[] bucketTails;
                return false;
            }
        }

        // każdy kubełek sortujemy osobno
        for (int i = 0; i < bucketCount; ++i) {
            insertionSortList(bucketHeads[i]);
        }

        int index = 0;
        // index wskazuje miejsce zapisu w strukturze wynikowej

        // przepisujemy dane z kubełków z powrotem do struktury
        for (int i = 0; i < bucketCount; ++i) {
            Node* current = bucketHeads[i];

            while (current != nullptr) {
                writeAt(structure, index, current->value);
                ++index;
                current = current->next;
            }
        }

        // zwalniamy pamięć po kubełkach
        clearBuckets(bucketHeads, bucketCount);
        delete[] bucketTails;

        return true;
    }

} // namespace

// uruchamia bucket sort dla tablicy
bool BucketSort::sort(Array<int>& array) {
    return bucketSortImpl(array);
}

// uruchamia bucket sort dla listy jednokierunkowej
bool BucketSort::sort(SingleList<int>& list) {
    return bucketSortImpl(list);
}

// uruchamia bucket sort dla listy dwukierunkowej
bool BucketSort::sort(DoubleList<int>& list) {
    return bucketSortImpl(list);
}