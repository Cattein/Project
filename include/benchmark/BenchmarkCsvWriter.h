//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_BENCHMARKCSVWRITER_H
#define PROJECT_BENCHMARKCSVWRITER_H

#include <string>
#include "benchmark/BenchmarkStats.h"

// klasa odpowiedzialna za dopisywanie wyników benchmarku do pliku csv
class BenchmarkCsvWriter {
public:
    // zapisuje jeden wynik benchmarku do pliku
    // stats - struktura z min, max i średnim czasem
    static bool appendResult(const std::string& filename, const BenchmarkStats& stats);
};

#endif //PROJECT_BENCHMARKCSVWRITER_H