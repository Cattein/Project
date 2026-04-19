//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_BENCHMARKSTATS_H
#define PROJECT_BENCHMARKSTATS_H

// struktura przechowująca końcowe wyniki benchmarku
struct BenchmarkStats {
    long long minTimeFinal;   // najmniejszy zmierzony czas
    long long maxTimeFinal;   // największy zmierzony czas
    double averageTimeFinal;  // średni czas ze wszystkich iteracji
};

#endif // PROJECT_BENCHMARKSTATS_H