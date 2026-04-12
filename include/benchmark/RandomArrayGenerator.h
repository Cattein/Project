//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_RANDOMARRAYGENERATOR_H
#define PROJECT_RANDOMARRAYGENERATOR_H

#include "structures/Array.h"

class RandomArrayGenerator {
public:
    static bool fillRandom(Array& array);
    static Array* copyArray(const Array& source);
};


#endif //PROJECT_RANDOMARRAYGENERATOR_H