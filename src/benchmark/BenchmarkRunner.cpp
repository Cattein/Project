//
// Created by MashaGuzhva on 12/04/2026.
//

#include "benchmark/BenchmarkRunner.h"

#include <iostream>
#include <chrono>
#include <string>

#include "Parameters.h"
#include "structures/Array.h"
#include "structures/SingleList.h"
#include "structures/DoubleList.h"
#include "structures/Stack.h"
#include "structures/BinaryTree.h"
#include "algorytmsSorting/QuickSort.h"
#include "algorytmsSorting/ShellSort.h"
#include "algorytmsSorting/BucketSort.h"
#include "checking/SortingCheck.h"
#include "benchmark/RandomArrayGenerator.h"

namespace {

    // sprawdza, czy wybrany wariant shellsorta jest obsługiwany
    bool isShellParameterSupported() {
        return Parameters::shellParameter != Parameters::ShellParameters::option3 &&
               Parameters::shellParameter != Parameters::ShellParameters::option4;
    }

    // wypełnia strukturę zgodnie z rozkładem wybranym w parametrach
    template <typename Structure>
    bool fillByDistribution(Structure& source) {
        if (Parameters::distribution == Parameters::Distribution::random) {
            return RandomArrayGenerator::fillRandom(source);
        }

        if (Parameters::distribution == Parameters::Distribution::ascending) {
            return RandomArrayGenerator::fillAscending(source);
        }

        if (Parameters::distribution == Parameters::Distribution::ascending50Per) {
            return RandomArrayGenerator::fillAscending50Per(source);
        }

        if (Parameters::distribution == Parameters::Distribution::descending) {
            return RandomArrayGenerator::fillDescending(source);
        }

        return false;
    }

    // ===== tworzenie struktur źródłowych =====

    template <typename T>
    bool createSource(Array<T>& source) {
        // tablica ma już ustalony rozmiar po konstruktorze
        return source.getSize() == Parameters::structureSize;
    }

    template <typename T>
    bool createSource(SingleList<T>& source) {
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(T{})) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    bool createSource(DoubleList<T>& source) {
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(T{})) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    bool createSource(Stack<T>& source) {
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.push(T{})) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    bool createSource(BinaryTree<T>& source) {
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(T{})) {
                return false;
            }
        }

        return true;
    }

    // ===== kopiowanie struktur =====

    template <typename T>
    Array<T>* copyStructure(const Array<T>& source) {
        return RandomArrayGenerator::copyArray(source);
    }

    template <typename T>
    SingleList<T>* copyStructure(const SingleList<T>& source) {
        return RandomArrayGenerator::copySingleList(source);
    }

    template <typename T>
    DoubleList<T>* copyStructure(const DoubleList<T>& source) {
        return RandomArrayGenerator::copyDoubleList(source);
    }

    template <typename T>
    Stack<T>* copyStructure(const Stack<T>& source) {
        return RandomArrayGenerator::copyStack(source);
    }

    template <typename T>
    BinaryTree<T>* copyStructure(const BinaryTree<T>& source) {
        return RandomArrayGenerator::copyBinaryTree(source);
    }

    // ===== wybór algorytmu sortowania =====

    template <typename T>
    bool sortStructure(Array<T>& array) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort::sort(array, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            ShellSort::sort(array, Parameters::shellParameter);
            return true;
        }

        std::cerr << "ERROR! Selected algorithm is not implemented for Array.\n";
        return false;
    }

    bool sortStructure(Array<int>& array) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if (!BucketSort::sort(array)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        }

        return sortStructure<int>(array);
    }

    template <typename T>
    bool sortStructure(SingleList<T>& list) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort::sort(list, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            ShellSort::sort(list, Parameters::shellParameter);
            return true;
        }

        std::cerr << "ERROR! Selected algorithm is not implemented for SingleList.\n";
        return false;
    }

    bool sortStructure(SingleList<int>& list) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if (!BucketSort::sort(list)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        }

        return sortStructure<int>(list);
    }

    template <typename T>
    bool sortStructure(DoubleList<T>& list) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort::sort(list, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            ShellSort::sort(list, Parameters::shellParameter);
            return true;
        }

        std::cerr << "ERROR! Selected algorithm is not implemented for DoubleList.\n";
        return false;
    }

    bool sortStructure(DoubleList<int>& list) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if (!BucketSort::sort(list)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        }

        return sortStructure<int>(list);
    }

    template <typename T>
    bool sortStructure(Stack<T>& stack) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort::sort(stack, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            ShellSort::sort(stack, Parameters::shellParameter);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            std::cerr << "ERROR! Bucket sort is not implemented for Stack.\n";
            return false;
        }

        std::cerr << "ERROR! Selected algorithm is not implemented for Stack.\n";
        return false;
    }

    template <typename T>
    bool sortStructure(BinaryTree<T>& tree) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            QuickSort::sort(tree, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            ShellSort::sort(tree, Parameters::shellParameter);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            std::cerr << "ERROR! Bucket sort is not implemented for BinaryTree.\n";
            return false;
        }

        std::cerr << "ERROR! Selected algorithm is not implemented for BinaryTree.\n";
        return false;
    }

    // ===== wspólna pętla benchmarku =====
    // każda iteracja:
    // 1. tworzy kopię danych źródłowych
    // 2. mierzy czas sortowania
    // 3. sprawdza poprawność wyniku
    // 4. aktualizuje min, max i średnią

    template <typename Structure>
    bool runBenchmarkLoop(const Structure& source, BenchmarkStats& stats, const std::string& structureName) {
        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            Structure* testStructure = copyStructure(source);
            // sortujemy kopię, żeby każda iteracja startowała z tych samych danych

            if (testStructure == nullptr) {
                std::cerr << "ERROR! Failed to copy source " << structureName << ".\n";
                return false;
            }

            const auto start = std::chrono::steady_clock::now();

            if (!sortStructure(*testStructure)) {
                delete testStructure;
                return false;
            }

            const auto end = std::chrono::steady_clock::now();

            if (!SortingCheck::SortedAscend(*testStructure)) {
                std::cerr << "ERROR! " << structureName << " is not sorted correctly.\n";
                delete testStructure;
                return false;
            }

            const auto elapsed =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            if (elapsed < minTime) {
                minTime = elapsed;
            }

            if (elapsed > maxTime) {
                maxTime = elapsed;
            }

            sumTime += elapsed;

            std::cout << "iteration " << (iteration + 1)
                      << " [us] = " << elapsed.count() << "\n";

            delete testStructure;
        }

        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    // ===== benchmark dla konkretnych struktur =====

    template <typename T>
    bool runArrayBenchmark(BenchmarkStats& stats) {
        Array<T> source(Parameters::structureSize);

        if (!createSource(source)) {
            std::cerr << "ERROR! Failed to create source array.\n";
            return false;
        }

        if (!fillByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }

        return runBenchmarkLoop(source, stats, "Array");
    }

    template <typename T>
    bool runSingleListBenchmark(BenchmarkStats& stats) {
        SingleList<T> source;

        if (!createSource(source)) {
            std::cerr << "ERROR! Failed to create source single list.\n";
            return false;
        }

        if (!fillByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }

        return runBenchmarkLoop(source, stats, "SingleList");
    }

    template <typename T>
    bool runDoubleListBenchmark(BenchmarkStats& stats) {
        DoubleList<T> source;

        if (!createSource(source)) {
            std::cerr << "ERROR! Failed to create source double list.\n";
            return false;
        }

        if (!fillByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }

        return runBenchmarkLoop(source, stats, "DoubleList");
    }

    template <typename T>
    bool runStackBenchmark(BenchmarkStats& stats) {
        Stack<T> source;

        if (!createSource(source)) {
            std::cerr << "ERROR! Failed to create source stack.\n";
            return false;
        }

        if (!fillByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }

        return runBenchmarkLoop(source, stats, "Stack");
    }

    template <typename T>
    bool runBinaryTreeBenchmark(BenchmarkStats& stats) {
        BinaryTree<T> source;

        if (!createSource(source)) {
            std::cerr << "ERROR! Failed to create source binary tree.\n";
            return false;
        }

        if (!fillByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }

        return runBenchmarkLoop(source, stats, "BinaryTree");
    }

} // namespace

bool BenchmarkRunner::run(BenchmarkStats& stats) {
    // ===== sprawdzanie parametrów =====

    if (Parameters::structureSize <= 0) {
        std::cerr << "ERROR! structureSize must be greater than 0.\n";
        return false;
    }

    if (Parameters::iterations <= 0) {
        std::cerr << "ERROR! iterations must be greater than 0.\n";
        return false;
    }

    if (Parameters::distribution == Parameters::Distribution::undefined) {
        std::cerr << "ERROR! distribution must be set in benchmark mode.\n";
        return false;
    }

    if (Parameters::algorithm == Parameters::Algorithms::quick &&
        Parameters::pivot == Parameters::Pivots::undefined) {
        std::cerr << "ERROR! pivot must be set for quick sort.\n";
        return false;
    }

    if (Parameters::algorithm == Parameters::Algorithms::shell &&
        Parameters::shellParameter == Parameters::ShellParameters::undefined) {
        std::cerr << "ERROR! shellParameter must be set for shell sort.\n";
        return false;
    }

    // ===== array =====

    if (Parameters::structure == Parameters::Structures::array) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runArrayBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runArrayBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runArrayBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runArrayBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runArrayBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runArrayBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runArrayBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runArrayBenchmark<unsigned char>(stats);

        std::cerr << "ERROR! This data type is not implemented for Array.\n";
        return false;
    }

    // ===== single list =====

    if (Parameters::structure == Parameters::Structures::singleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runSingleListBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runSingleListBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runSingleListBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runSingleListBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runSingleListBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runSingleListBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runSingleListBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runSingleListBenchmark<unsigned char>(stats);

        std::cerr << "ERROR! This data type is not implemented for SingleList.\n";
        return false;
    }

    // ===== double list =====

    if (Parameters::structure == Parameters::Structures::doubleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runDoubleListBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runDoubleListBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runDoubleListBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runDoubleListBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runDoubleListBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runDoubleListBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runDoubleListBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runDoubleListBenchmark<unsigned char>(stats);

        std::cerr << "ERROR! This data type is not implemented for DoubleList.\n";
        return false;
    }

    // ===== stack =====

    if (Parameters::structure == Parameters::Structures::stack) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runStackBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runStackBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runStackBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runStackBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runStackBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runStackBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runStackBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runStackBenchmark<unsigned char>(stats);

        std::cerr << "ERROR! This data type is not implemented for Stack.\n";
        return false;
    }

    // ===== binary tree =====

    if (Parameters::structure == Parameters::Structures::binaryTree) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runBinaryTreeBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runBinaryTreeBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runBinaryTreeBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runBinaryTreeBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runBinaryTreeBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runBinaryTreeBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runBinaryTreeBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runBinaryTreeBenchmark<unsigned char>(stats);

        std::cerr << "ERROR! This data type is not implemented for BinaryTree.\n";
        return false;
    }

    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}