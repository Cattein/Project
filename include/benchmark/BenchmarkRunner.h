//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_BENCHMARKRUNNER_H
#define PROJECT_BENCHMARKRUNNER_H

#include "benchmark/BenchmarkStats.h"

// klasa odpowiedzialna za uruchomienie całego benchmarku
class BenchmarkRunner {
public:
    // wykonuje benchmark zgodnie z parametrami ustawionymi w Parameters
    // stats -  zapisane końcowe wyniki (minimalny, maksymalny i średni czas wykonania)
    static bool run(BenchmarkStats& stats);
};

#endif // PROJECT_BENCHMARKRUNNER_H