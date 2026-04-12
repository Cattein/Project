//
// Created by MashaGuzhva on 12/04/2026.
//

#ifndef PROJECT_BENCHMARKCSVWRITER_H
#define PROJECT_BENCHMARKCSVWRITER_H

#include <string>
#include "benchmark/BenchmarkStats.h"

class BenchmarkCsvWriter {
public:
    static bool appendResult(const std::string& filename, const BenchmarkStats& stats);
};

#endif //PROJECT_BENCHMARKCSVWRITER_H