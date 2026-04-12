//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_RANDOMARRAYGENERATOR_H
#define PROJECT_RANDOMARRAYGENERATOR_H

#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"


class RandomArrayGenerator {
public:
    static bool fillRandom(Array& array);
    static bool fillRandom(SingleList& list);
    static bool fillRandom(DoubleList& list);

    static Array* copyArray(const Array& source);
    static SingleList* copySingleList(const SingleList& source);
    static DoubleList* copyDoubleList(const DoubleList& source);






};


#endif //PROJECT_RANDOMARRAYGENERATOR_H