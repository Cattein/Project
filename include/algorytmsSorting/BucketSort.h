//
// Created by MashaGuzhva on 11/04/2026.
//

#ifndef PROJECT_BUCKETSORT_H
#define PROJECT_BUCKETSORT_H

#include <new>
#include <string>
#include <type_traits>

#include "structures/Array.h"
#include "structures/DoubleList.h"
#include "structures/SingleList.h"

class BucketSort {
private:
    // BucketTraits odpowiada tylko za sposób wyznaczania liczby kubełków
    // oraz indeksu kubełka dla konkretnego typu T.
    // Sama logika Bucket Sort pozostaje jedna i szablonowa.
    template <typename T>
    struct BucketTraits {
        static constexpr bool supported =
            std::is_arithmetic<T>::value || std::is_same<T, std::string>::value;

        static int bucketCount(int size) {
            if constexpr (std::is_same<T, std::string>::value) {
                // kubełek 0 dla pustego napisu, 1..256 dla możliwych wartości unsigned char
                return 257;
            } else {
                return size;
            }
        }

        static int getBucketIndex(const T& value,
                                  const T& minValue,
                                  const T& maxValue,
                                  int bucketCount) {
            if constexpr (std::is_same<T, std::string>::value) {
                // Dla napisów nie ma operacji odejmowania ani liczbowego zakresu min-max,
                // dlatego rozdzielamy je do kubełków według pierwszego znaku.
                // Dokładne uporządkowanie w kubełku robi operator < dla std::string.
                (void) minValue;
                (void) maxValue;

                if (value.empty()) {
                    return 0;
                }

                int bucketIndex = static_cast<int>(static_cast<unsigned char>(value[0])) + 1;

                if (bucketIndex < 0) {
                    bucketIndex = 0;
                }

                if (bucketIndex >= bucketCount) {
                    bucketIndex = bucketCount - 1;
                }

                return bucketIndex;
            } else {
                // Wariant dla typów liczbowych: int, float, double, char, unsigned itd.
                // Indeks kubełka wyznaczamy na podstawie położenia wartości w zakresie min-max.
                if (bucketCount <= 1 || minValue == maxValue) {
                    return 0;
                }

                const long double minAsLongDouble = static_cast<long double>(minValue);
                const long double maxAsLongDouble = static_cast<long double>(maxValue);
                const long double valueAsLongDouble = static_cast<long double>(value);
                const long double range = maxAsLongDouble - minAsLongDouble;

                if (range <= 0.0L) {
                    return 0;
                }

                const long double normalized = (valueAsLongDouble - minAsLongDouble) / range;
                int bucketIndex = static_cast<int>(normalized * static_cast<long double>(bucketCount - 1));

                if (bucketIndex < 0) {
                    bucketIndex = 0;
                }

                if (bucketIndex >= bucketCount) {
                    bucketIndex = bucketCount - 1;
                }

                return bucketIndex;
            }
        }
    };

    // Każdy kubełek przechowujemy jako prostą listę jednokierunkową.
    template <typename T>
    struct Node {
        T value;
        Node* next;

        explicit Node(const T& newValue) : value(newValue), next(nullptr) {}
    };

    // Dodaje element na koniec listy kubełka.
    template <typename T>
    static bool pushBack(Node<T>*& head, Node<T>*& tail, const T& value) {
        Node<T>* newNode = new (std::nothrow) Node<T>(value);

        if (newNode == nullptr) {
            return false;
        }

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        return true;
    }

    // Sortuje jeden kubełek insertion sortem.
    template <typename T>
    static void insertionSortList(Node<T>*& head) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Node<T>* sorted = nullptr;

        while (head != nullptr) {
            Node<T>* current = head;
            head = head->next;

            if (sorted == nullptr || current->value < sorted->value) {
                current->next = sorted;
                sorted = current;
            } else {
                Node<T>* temp = sorted;

                while (temp->next != nullptr && !(current->value < temp->next->value)) {
                    temp = temp->next;
                }

                current->next = temp->next;
                temp->next = current;
            }
        }

        head = sorted;
    }

    // Zwalnia wszystkie kubełki oraz tablicę wskaźników na głowy kubełków.
    template <typename T>
    static void clearBuckets(Node<T>** heads, int bucketCount) {
        if (heads == nullptr) {
            return;
        }

        for (int i = 0; i < bucketCount; ++i) {
            Node<T>* current = heads[i];

            while (current != nullptr) {
                Node<T>* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        delete[] heads;
    }

    // Wspólny odczyt wartości ze struktury indeksowanej.
    // Działa dla Array, SingleList i DoubleList, bo każda ma get(index, value).
    template <typename Structure, typename T>
    static bool readAt(const Structure& structure, int index, T& value) {
        return structure.get(index, value);
    }

    // Wspólny zapis wartości do struktury indeksowanej.
    // Działa dla Array, SingleList i DoubleList, bo każda ma set(index, value).
    template <typename Structure, typename T>
    static bool writeAt(Structure& structure, int index, const T& value) {
        return structure.set(index, value);
    }

    // Jedna wspólna implementacja Bucket Sort dla różnych struktur i typów.
    // Różni się tylko BucketTraits<T>, czyli sposób wyznaczania indeksu kubełka.
    template <typename Structure, typename T>
    static bool sortImpl(Structure& structure) {
        if constexpr (!BucketTraits<T>::supported) {
            return false;
        } else {
            const int size = structure.getSize();

            if (size <= 1) {
                return true;
            }

            T minValue{};
            T maxValue{};

            if (!readAt<Structure, T>(structure, 0, minValue)) {
                return false;
            }

            maxValue = minValue;

            for (int i = 1; i < size; ++i) {
                T value{};

                if (!readAt<Structure, T>(structure, i, value)) {
                    return false;
                }

                if (value < minValue) {
                    minValue = value;
                }

                if (maxValue < value) {
                    maxValue = value;
                }
            }

            const int bucketCount = BucketTraits<T>::bucketCount(size);

            if (bucketCount <= 0) {
                return false;
            }

            Node<T>** bucketHeads = new (std::nothrow) Node<T>*[bucketCount];
            Node<T>** bucketTails = new (std::nothrow) Node<T>*[bucketCount];

            if (bucketHeads == nullptr || bucketTails == nullptr) {
                delete[] bucketHeads;
                delete[] bucketTails;
                return false;
            }

            for (int i = 0; i < bucketCount; ++i) {
                bucketHeads[i] = nullptr;
                bucketTails[i] = nullptr;
            }

            for (int i = 0; i < size; ++i) {
                T value{};

                if (!readAt<Structure, T>(structure, i, value)) {
                    clearBuckets(bucketHeads, bucketCount);
                    delete[] bucketTails;
                    return false;
                }

                const int bucketIndex = BucketTraits<T>::getBucketIndex(
                    value,
                    minValue,
                    maxValue,
                    bucketCount
                );

                if (!pushBack(bucketHeads[bucketIndex], bucketTails[bucketIndex], value)) {
                    clearBuckets(bucketHeads, bucketCount);
                    delete[] bucketTails;
                    return false;
                }
            }

            for (int i = 0; i < bucketCount; ++i) {
                insertionSortList(bucketHeads[i]);
            }

            int index = 0;

            for (int i = 0; i < bucketCount; ++i) {
                Node<T>* current = bucketHeads[i];

                while (current != nullptr) {
                    if (!writeAt<Structure, T>(structure, index, current->value)) {
                        clearBuckets(bucketHeads, bucketCount);
                        delete[] bucketTails;
                        return false;
                    }

                    ++index;
                    current = current->next;
                }
            }

            clearBuckets(bucketHeads, bucketCount);
            delete[] bucketTails;

            return true;
        }
    }

public:
    template <typename T>
    static bool sort(Array<T>& array) {
        return sortImpl<Array<T>, T>(array);
    }

    template <typename T>
    static bool sort(SingleList<T>& list) {
        return sortImpl<SingleList<T>, T>(list);
    }

    template <typename T>
    static bool sort(DoubleList<T>& list) {
        return sortImpl<DoubleList<T>, T>(list);
    }
};

#endif // PROJECT_BUCKETSORT_H
