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
    static bool fillRandom(Array<int>& array);
    static bool fillRandom(SingleList<int>& list);
    static bool fillRandom(DoubleList<int>& list);

    static Array<int>* copyArray(const Array<int>& source);
    static SingleList<int>* copySingleList(const SingleList<int>& source);
    static DoubleList<int>* copyDoubleList(const DoubleList<int>& source);






};


#endif //PROJECT_RANDOMARRAYGENERATOR_H