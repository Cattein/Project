//
// Created by MashaGuzhva on 11/04/2026.
//

#include "algorytmsSorting/BucketSort.h"
#include <new>

// anonymous namespace
// wszystko zapisane tutaj jest widoczne tylko w tym pliku
namespace {

    // prosty węzeł listy jednokierunkowej
    // każdy kubełek będzie przechowywany właśnie jako taka lista
    struct Node {
        int value;    // value przechowuje liczbę z tablicy
        Node* next;   // next wskazuje na następny element listy
        // jeśli next == nullptr, to znaczy, że to ostatni element

        // explicit chroni przed przypadkową zamianą int na Node, tworzymy nowy węzeł z podaną wartością
        explicit Node(int newValue) : value(newValue), next(nullptr) {}
    };

    // dodaje nowy element na koniec listy
    // Node*& oznacza referencję do wskaźnika
    bool pushBack(Node*& head, Node*& tail, int value) {
        // tworzymy nowy węzeł
        // std::nothrow - przy braku pamięci dostaniemy nullptr
        Node* newNode = new (std::nothrow) Node(value);

        // jeśli pamięć nie została przydzielona, kończymy błędem
        if (newNode == nullptr) {
            return false;
        }

        // jeśli lista była pusta
        // nowy element staje się jednocześnie początkiem i końcem
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            // jeśli lista nie była pusta - dopinamy nowy element na koniec
            tail->next = newNode;
            tail = newNode;
        }

        // element został poprawnie dodany
        return true;
    }

    // sortuje pojedynczą listę za pomocą insertion sorta
    // każda lista reprezentuje jeden kubełek
    void insertionSortList(Node*& head) {
        // jeśli lista jest pusta albo ma tylko jeden element
        // to nic nie trzeba sortować
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Node* sorted = nullptr;    // nową posortowaną listę

        // bierzemy po kolei elementy ze starej listy
        while (head != nullptr) {
            Node* current = head;    // current - el. który chcemy wstawić do listy sorted
            head = head->next;
            // przesuwamy head dalej -  current jest już odłączony od początku starej listy

            // jeśli lista sorted jest pusta or current powinien trafić na sam początek
            if (sorted == nullptr || current->value < sorted->value) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;   // zaczynamy szukać miejsca w posortowanej liście

                // idziemy dalej, dopóki następny element jest mniejszy lub równy current
                while (temp->next != nullptr && temp->next->value <= current->value) {
                    temp = temp->next;
                }

                current->next = temp->next;    // wstawiamy current za elementem temp
                temp->next = current;
            }
        }

        head = sorted;
    }

    // usuwa wszystkie listy w kubełkach, a na końcu usuwa tablicę wskaźników
    void clearBuckets(Node** heads, int bucketCount) {

        // przechodzimy po wszystkich kubełkach
        for (int i = 0; i < bucketCount; ++i) {
            Node* current = heads[i];    // current wskazuje na pierwszy element listy w danym kubełku

            // usuwamy całą listę element po elemencie
            while (current != nullptr) {
                Node* nextNode = current->next;     // zapamiętujemy kolejny element, zanim usuniemy current
                delete current;    // zwalniamy pamięć bieżącego węzła
                current = nextNode;    // przechodzimy do następnego elementu
            }
        }

        delete[] heads;    // po usunięciu wszystkich list usuwamy tablicę kubełków
    }

    // ===== odczyt i zapis dla Array =====

    int readAt(const Array<int>& array, int index) {
        // const Array& oznacza, że tablica jest przekazywana bez kopiowania
        // const oznacza, że tej tablicy nie można tutaj zmieniać
        return array.setId(index);
    }

    void writeAt(Array<int>& array, int index, int value) {
        // Array& - tablica jest przekazywana przez odwołanie
        array.setId(index) = value;
    }

    // ===== odczyt i zapis dla SingleList =====

    int readAt(const SingleList<int>& list, int index) {
        int value = 0;
        // value chwilowo przechowuje odczytaną liczbę

        list.get(index, value);
        // get wpisuje wartość spod danego indeksu do zmiennej value

        return value;
    }

    void writeAt(SingleList<int>& list, int index, int value) {
        list.set(index, value);
        // set podmienia wartość na wskazanej pozycji
    }

    // ===== odczyt i zapis dla DoubleList =====

    int readAt(const DoubleList<int>& list, int index) {
        int value = 0;
        // value chwilowo przechowuje odczytaną liczbę

        list.get(index, value);
        // get wpisuje wartość spod danego indeksu do zmiennej value

        return value;
    }

    void writeAt(DoubleList<int>& list, int index, int value) {
        list.set(index, value);
        // set podmienia wartość na wskazanej pozycji
    }

    // ===== wspólna implementacja BucketSort =====

    // template pozwala napisać jedną wspólną funkcję dla różnych struktur
    // Structure będzie tutaj zastąpione prawdziwym typem
    // może to być Array, SingleList albo DoubleList
    template <typename Structure>
    bool bucketSortImpl(Structure& structure) {
        const int size = structure.getSize();    // rozmiar struktury
        // const oznacza, że tej wartości nie zmieniamy po utworzeniu

        // jeśli struktura jest pusta albo ma jeden element - posortowana
        if (size <= 1) {
            return true;
        }

        // na początku zakładamy, że pierwszy element jest jednocześnie najmniejszy i największy
        int minValue = readAt(structure, 0);
        int maxValue = readAt(structure, 0);

        // szukamy prawdziwej wartości minimalnej i maksymalnej
        for (int i = 1; i < size; ++i) {
            const int value = readAt(structure, i);   // pobieramy aktualną wartość ze struktury

            // jeśli aktualny element jest mniejszy od minValue - aktualizujemy minimum
            if (value < minValue) {
                minValue = value;
            }

            // jeśli aktualny element jest większy od maxValue - aktualizujemy maksimum
            if (value > maxValue) {
                maxValue = value;
            }
        }

        // jeśli min i max są równe - wszystkie liczby są takie same
        if (minValue == maxValue) {
            return true;
        }

        // ustalamy liczbę kubełków ( kubełków - ile jest elementów)
        const int bucketCount = size;

        // bucketHeads początek każdej listy
        Node** bucketHeads = new (std::nothrow) Node*[bucketCount];

        // bucketTails koniec każdej listy
        Node** bucketTails = new (std::nothrow) Node*[bucketCount];

        // jeśli nie udało się utworzyć jednej z tablic
        // trzeba posprzątać to, co udało się już zaalokować
        if (bucketHeads == nullptr || bucketTails == nullptr) {
            delete[] bucketHeads;
            delete[] bucketTails;
            return false;
        }

        // na początku każdy kubełek jest pusty
        for (int i = 0; i < bucketCount; ++i) {
            bucketHeads[i] = nullptr;
            bucketTails[i] = nullptr;
        }

        // rozdzielamy elementy struktury do kubełków
        for (int i = 0; i < size; ++i) {
            const int value = readAt(structure, i);   // pobieramy aktualną wartość ze struktury

            // normalized przelicza wartość do zakresu od 0 do 1
            // minValue daje 0
            // maxValue daje 1
            const double normalized =
                (static_cast<double>(value) - static_cast<double>(minValue)) /
                (static_cast<double>(maxValue) - static_cast<double>(minValue));
            // static_cast<double> zamienia liczbę na double
            // dzięki temu nie stracimy części ułamkowej przy dzieleniu

            // na podstawie normalized obliczamy numer kubełka
            int bucketIndex = static_cast<int>(normalized * (bucketCount - 1));

            // dodatkowe zabezpieczenie na wypadek problemów z obliczeniami
            if (bucketIndex < 0) {
                bucketIndex = 0;
            }

            // zabezpieczenie górnej granicy
            if (bucketIndex >= bucketCount) {
                bucketIndex = bucketCount - 1;
            }

            // dodajemy wartość do odpowiedniego kubełka
            // jeśli się nie uda, trzeba zwolnić pamięć i zakończyć działanie
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

        int index = 0;    // index - gdzie wpisujemy kolejne elementy do struktury wynikowej

        // przepisujemy elementy z kubełków z powrotem do struktury
        for (int i = 0; i < bucketCount; ++i) {
            Node* current = bucketHeads[i];    // zaczynamy od początku listy w danym kubełku

            while (current != nullptr) {
                writeAt(structure, index, current->value);    // wpisujemy wartość z listy do struktury
                ++index;
                current = current->next;    // przechodzimy do następnego elementu listy
            }
        }

        // sprzątamy pamięć
        clearBuckets(bucketHeads, bucketCount);
        delete[] bucketTails;

        // jeśli doszliśmy tutaj, sortowanie się udało
        return true;
    }

} // namespace

// uruchamia bucketsort dla tablicy
bool BucketSort::sort(Array<int>& array) {
    return bucketSortImpl(array);
}

// uruchamia bucketsort dla listy jednokierunkowej
bool BucketSort::sort(SingleList<int>& list) {
    return bucketSortImpl(list);
}

// uruchamia bucketsort dla listy dwukierunkowej
bool BucketSort::sort(DoubleList<int>& list) {
    return bucketSortImpl(list);
}