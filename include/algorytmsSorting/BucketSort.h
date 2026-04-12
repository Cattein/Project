//
// Created by MashaGuzhva on 11/04/2026.
//

#ifndef PROJECT_BUCKETSORT_H
#define PROJECT_BUCKETSORT_H
#include "structures/Array.h"
#include "structures/DoubleList.h"
#include "structures/SingleList.h"


class BucketSort {
public:
    static bool sort(Array& array);
    static bool sort(SingleList& array);
    static bool sort(DoubleList& array);

};

#endif //PROJECT_BUCKETSORT_H