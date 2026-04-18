//
// Created by MashaGuzhva on 10/04/2026.
//

#ifndef PROJECT_SORTINGCHECK_H
#define PROJECT_SORTINGCHECK_H

#include "structures/Array.h"
#include "structures/DoubleList.h"
#include "structures/SingleList.h"
#include "structures/Stack.h"

class SortingCheck {
private:
    // template pozwala napisać jedną wspólną funkcję dla różnych typów struktur
    // Structure będzie tutaj zastąpione prawdziwym typem, np Array<int> albo SingleList<double>
    template <typename Structure, typename T>
    static bool sortedAscendImpl(const Structure& structure) {
        // const Structure& - struktura jest przekazywana bez kopiowania
        // const - funkcja tylko sprawdza dane i nie może ich zmieniać

        // zaczynamy od drugiego elementu
        // wtedy możemy porównać go z poprzednim
        for (int i = 1; i < structure.getSize(); ++i) {
            T last{};      // poprzedni element
            T current{};   // aktualny element
            // {} oznacza domyślną inicjalizację zmiennej

            // jeśli odczyt się nie uda, zwracamy false
            if (!structure.get(i - 1, last) || !structure.get(i, current)) {
                return false;
            }

            // jeśli aktualny element jest mniejszy od poprzedniego
            // struktura nie jest posortowana rosnąco
            if (current < last) {
                return false;
            }
        }

        return true;
    }

public:
    // sprawdza sortowanie dla stosu dowolnego typu T
    template <typename T>
    static bool SortedAscend(const Stack<T>& stack) {
        return sortedAscendImpl<Stack<T>, T>(stack);
    }

    // sprawdza sortowanie dla tablicy dowolnego typu T
    template <typename T>
    static bool SortedAscend(const Array<T>& array) {
        return sortedAscendImpl<Array<T>, T>(array);
    }

    // sprawdza sortowanie dla listy jednokierunkowej dowolnego typu T
    template <typename T>
    static bool SortedAscend(const SingleList<T>& list) {
        return sortedAscendImpl<SingleList<T>, T>(list);
    }

    // sprawdza sortowanie dla listy dwukierunkowej dowolnego typu T
    template <typename T>
    static bool SortedAscend(const DoubleList<T>& list) {
        return sortedAscendImpl<DoubleList<T>, T>(list);
    }
};

#endif //PROJECT_SORTINGCHECK_H