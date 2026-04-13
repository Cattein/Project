//
// Created by MashaGuzhva on 10/04/2026.
//

#include "checking/SortingCheck.h"

// template pozwala napisać jedną wspólną funkcję dla różnych typów struktur
// typename T oznacza, że T będzie zastąpione prawdziwym typem
// tutaj może to być na przykład Array albo SingleList
namespace {
    template <typename T>
    bool sortedAscendImpl(const T& structure) {
        // const T& oznacza, że struktura jest przekazywana przez referencję bez kopiowania
        // const oznacza, że funkcja tylko sprawdza dane i nie może ich zmieniać

        // zaczynamy od drugiego elementu
        // wtedy możemy porównać go z poprzednim
        for (int i = 1; i < structure.getSize(); ++i) {

            int last = 0; // last przechowuje poprzednią wartość
            int current = 0;// current przechowuje bieżącą wartość

            // próbujemy odczytać dwa sąsiednie elementy
            // jeśli odczyt się nie uda, zwracamy false
            if (!structure.get(i - 1, last) || !structure.get(i, current)) {
                return false;
            }

            // jeśli bieżący element jest mniejszy od poprzedniego
            // to struktura nie jest posortowana rosnąco
            if (current < last) {
                return false;
            }
        }

        // jeśli żaden element nie złamał kolejności rosnącej
        // to struktura jest posortowana
        return true;
    }
}

// sprawdza sortowanie dla tablicy
bool SortingCheck::SortedAscend(const Array<int>& array) {
    return sortedAscendImpl(array);
}

// funkcja sprawdza sortowanie dla listy jednokierunkowej
// korzysta z tej samej wspólnej funkcji
bool SortingCheck::SortedAscend(const SingleList<int>& list) {
    return sortedAscendImpl(list);
}

// funkcja sprawdza sortowanie dla listy dwukierunkowej
// korzysta z tej samej wspólnej funkcji
bool SortingCheck::SortedAscend(const DoubleList<int>& list) {
    return sortedAscendImpl(list);
}