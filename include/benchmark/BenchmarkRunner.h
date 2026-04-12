//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_BENCHMARKRUNNER_H
#define PROJECT_BENCHMARKRUNNER_H

#include "benchmark/BenchmarkStats.h"
class BenchmarkRunner {
public:
    static bool run(BenchmarkStats& stats);
};

#endif //PROJECT_BENCHMARKRUNNER_H