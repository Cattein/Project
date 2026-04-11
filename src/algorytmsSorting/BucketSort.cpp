//
// Created by MashaGuzhva on 11/04/2026.
//
#include "algorytmsSorting/BucketSort.h"
#include <new>

struct Node {
    int value;
    Node* next;

    explicit Node(int newValue) : value(newValue), next(nullptr) {}
};

static void clearBuckets(Node** buckets, int bucketCount) {
    for (int i = 0; i < bucketCount; ++i) {

        Node* current = buckets[i];
        while (current != nullptr) {

            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    delete[] buckets;
}

static bool insertSorted(Node*& head, int value) {
    Node* newNode = new (std::nothrow) Node(value);

    if (newNode == nullptr) {
        return false;
    }



    if (head == nullptr || value < head->value) {
        newNode->next = head;
        head = newNode;
        return true;
    }
    Node* current = head;

    while (current->next != nullptr && current->next->value <= value) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    return true;
}

bool BucketSort::sort(Array& array) {


    const int size = array.getSize();

    if (size <= 1) {
        return true;
    }

    int minValue = array.setId(0);
    int maxValue = array.setId(0);

    for (int i = 1; i < size; ++i) {

        const int value = array.setId(i);
        if (value < minValue) {
            minValue = value;
        }

        if (value > maxValue) {
            maxValue = value;
        }
    }

    if (minValue == maxValue) {
        return true;
    }

    const int bucketCount = size;

    Node** buckets = new (std::nothrow) Node*[bucketCount];






    if (buckets == nullptr) {
        return false;
    }

    for (int i = 0; i < bucketCount; ++i) {
        buckets[i] = nullptr;
    }

    const long long range =
        static_cast<long long>(maxValue) - static_cast<long long>(minValue);

    for (int i = 0; i < size; ++i) {
        const int value = array.setId(i);

        const long long normalized =
            static_cast<long long>(value) - static_cast<long long>(minValue);

        int bucketIndex =
            static_cast<int>((normalized * (bucketCount - 1)) / range);

        if (bucketIndex < 0) {
            bucketIndex = 0;
        }



        if (bucketIndex >= bucketCount) {
            bucketIndex = bucketCount - 1;
        }

        if (!insertSorted(buckets[bucketIndex], value)) {
            clearBuckets(buckets, bucketCount);
            return false;
        }
    }

    int arrayIndex = 0;
    for (int i = 0; i < bucketCount; ++i) {
        Node* current = buckets[i];

        while (current != nullptr) {


            array.setId(arrayIndex) = current->value;
            ++arrayIndex;
            current = current->next;
        }
    }

    clearBuckets(buckets, bucketCount);

















    return true;
}