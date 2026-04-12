#include "benchmark/BenchmarkRunner.h"

#include <iostream>
#include <chrono>

#include "Parameters.h"
#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "algorytmsSorting/QuickSort.h"
#include "algorytmsSorting/ShellSort.h"
#include "algorytmsSorting/BucketSort.h"
#include "checking/SortingCheck.h"
#include "benchmark/RandomArrayGenerator.h"

static bool areBenchmarkParametersValid() {
    if (Parameters::structureSize <= 0) {
        std::cerr << "ERROR! structureSize must be greater than 0.\n";
        return false;
    }

    if (Parameters::iterations <= 0) {
        std::cerr << "ERROR! iterations must be greater than 0.\n";
        return false;
    }

    return true;
}

static bool isShellParameterSupported() {
    return Parameters::shellParameter != Parameters::ShellParameters::option3 &&
           Parameters::shellParameter != Parameters::ShellParameters::option4;
}

static void updateStats(
    const std::chrono::microseconds& elapsed,
    std::chrono::microseconds& minTime,
    std::chrono::microseconds& maxTime,
    std::chrono::microseconds& sumTime
) {
    if (elapsed < minTime) {
        minTime = elapsed;
    }

    if (elapsed > maxTime) {
        maxTime = elapsed;
    }

    sumTime += elapsed;
}

static void saveFinalStats(
    BenchmarkStats& stats,
    const std::chrono::microseconds& minTime,
    const std::chrono::microseconds& maxTime,
    const std::chrono::microseconds& sumTime
) {
    stats.minTimeFinal = minTime.count();
    stats.maxTimeFinal = maxTime.count();
    stats.averageTimeFinal = static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);
}

static bool sortArrayBenchmark(Array& array) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(array, Parameters::pivot);
        return true;
    }
    else if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
            return false;
        }

        ShellSort::sort(array, Parameters::shellParameter);
        return true;
    }
    else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
        if (!BucketSort::sort(array)) {
            std::cerr << "ERROR! Bucket sort failed.\n";
            return false;
        }

        return true;
    }

    std::cerr << "ERROR! Selected algorithm is not implemented.\n";
    return false;
}

static bool sortSingleListBenchmark(SingleList& list) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }
    else if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
            return false;
        }

        ShellSort::sort(list, Parameters::shellParameter);
        return true;
    }

    std::cerr << "ERROR! This algorithm is not implemented for SingleList yet.\n";
    return false;
}

static bool sortDoubleListBenchmark(DoubleList& list) {
    if (Parameters::algorithm == Parameters::Algorithms::quick) {
        QuickSort::sort(list, Parameters::pivot);
        return true;
    }
    else if (Parameters::algorithm == Parameters::Algorithms::shell) {
        if (!isShellParameterSupported()) {
            std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
            return false;
        }

        ShellSort::sort(list, Parameters::shellParameter);
        return true;
    }

    std::cerr << "ERROR! This algorithm is not implemented for DoubleList yet.\n";
    return false;
}

static bool runArrayBenchmark(BenchmarkStats& stats) {
    Array source(Parameters::structureSize);

    if (!RandomArrayGenerator::fillRandom(source)) {
        std::cerr << "ERROR! Failed to generate random data.\n";
        return false;
    }

    auto minTime = std::chrono::microseconds::max();
    auto maxTime = std::chrono::microseconds::zero();
    auto sumTime = std::chrono::microseconds::zero();

    for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
        Array* testArray = RandomArrayGenerator::copyArray(source);

        if (testArray == nullptr) {
            std::cerr << "ERROR! Failed to copy source array.\n";
            return false;
        }

        auto start = std::chrono::steady_clock::now();

        if (!sortArrayBenchmark(*testArray)) {
            delete testArray;
            return false;
        }

        auto end = std::chrono::steady_clock::now();

        if (!SortingCheck::SortedAscend(*testArray)) {
            std::cerr << "ERROR! Array is not sorted correctly.\n";
            delete testArray;
            return false;
        }

        const auto elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        updateStats(elapsed, minTime, maxTime, sumTime);

        std::cout << "iteration " << (iteration + 1)
                  << " [us] = " << elapsed.count() << "\n";

        delete testArray;
    }

    saveFinalStats(stats, minTime, maxTime, sumTime);
    return true;
}

static bool runSingleListBenchmark(BenchmarkStats& stats) {
    SingleList source;

    for (int i = 0; i < Parameters::structureSize; ++i) {
        if (!source.pushBack(0)) {
            std::cerr << "ERROR! Failed to create source single list.\n";
            return false;
        }
    }

    if (!RandomArrayGenerator::fillRandom(source)) {
        std::cerr << "ERROR! Failed to generate random data.\n";
        return false;
    }

    auto minTime = std::chrono::microseconds::max();
    auto maxTime = std::chrono::microseconds::zero();
    auto sumTime = std::chrono::microseconds::zero();

    for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
        SingleList* testList = RandomArrayGenerator::copySingleList(source);

        if (testList == nullptr) {
            std::cerr << "ERROR! Failed to copy source single list.\n";
            return false;
        }

        auto start = std::chrono::steady_clock::now();

        if (!sortSingleListBenchmark(*testList)) {
            delete testList;
            return false;
        }

        auto end = std::chrono::steady_clock::now();

        if (!SortingCheck::SortedAscend(*testList)) {
            std::cerr << "ERROR! SingleList is not sorted correctly.\n";
            delete testList;
            return false;
        }

        const auto elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        updateStats(elapsed, minTime, maxTime, sumTime);

        std::cout << "iteration " << (iteration + 1)
                  << " [us] = " << elapsed.count() << "\n";

        delete testList;
    }

    saveFinalStats(stats, minTime, maxTime, sumTime);
    return true;
}

static bool runDoubleListBenchmark(BenchmarkStats& stats) {
    DoubleList source;

    for (int i = 0; i < Parameters::structureSize; ++i) {
        if (!source.pushBack(0)) {
            std::cerr << "ERROR! Failed to create source double list.\n";
            return false;
        }
    }

    if (!RandomArrayGenerator::fillRandom(source)) {
        std::cerr << "ERROR! Failed to generate random data.\n";
        return false;
    }

    auto minTime = std::chrono::microseconds::max();
    auto maxTime = std::chrono::microseconds::zero();
    auto sumTime = std::chrono::microseconds::zero();

    for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
        DoubleList* testList = RandomArrayGenerator::copyDoubleList(source);

        if (testList == nullptr) {
            std::cerr << "ERROR! Failed to copy source double list.\n";
            return false;
        }

        auto start = std::chrono::steady_clock::now();

        if (!sortDoubleListBenchmark(*testList)) {
            delete testList;
            return false;
        }

        auto end = std::chrono::steady_clock::now();

        if (!SortingCheck::SortedAscend(*testList)) {
            std::cerr << "ERROR! DoubleList is not sorted correctly.\n";
            delete testList;
            return false;
        }

        const auto elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        updateStats(elapsed, minTime, maxTime, sumTime);

        std::cout << "iteration " << (iteration + 1)
                  << " [us] = " << elapsed.count() << "\n";

        delete testList;
    }

    saveFinalStats(stats, minTime, maxTime, sumTime);
    return true;
}

bool BenchmarkRunner::run(BenchmarkStats& stats) {
    if (!areBenchmarkParametersValid()) {
        return false;
    }

    if (Parameters::structure == Parameters::Structures::array) {
        return runArrayBenchmark(stats);
    }

    if (Parameters::structure == Parameters::Structures::singleList) {
        return runSingleListBenchmark(stats);
    }

    if (Parameters::structure == Parameters::Structures::doubleList) {
        return runDoubleListBenchmark(stats);
    }

    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}