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
#include "algorytmsSorting/QuickSort.h"
#include "algorytmsSorting/ShellSort.h"
#include "algorytmsSorting/BucketSort.h"
#include "checking/SortingCheck.h"
#include "benchmark/RandomArrayGenerator.h"

namespace {

    template <typename T>
    bool fillArrayByDistribution(Array<T>& source) {
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

    template <typename T>
    bool fillSingleListByDistribution(SingleList<T>& source) {
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

    template <typename T>
    bool fillDoubleListByDistribution(DoubleList<T>& source) {
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

    template <typename T>
    bool fillStackByDistribution(Stack<T>& source) {
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

    // sprawdza, czy wybrany wariant shellsorta jest obsługiwany
    bool isShellParameterSupported() {
        return Parameters::shellParameter != Parameters::ShellParameters::option3 &&
               Parameters::shellParameter != Parameters::ShellParameters::option4;
    }

    // ===== wybór algorytmu dla tablicy =====

    template <typename T>
    bool sortArray(Array<T>& array) {
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

        std::cerr << "ERROR! Selected algorithm is not implemented for this data type.\n";
        return false;
    }

    bool sortArray(Array<int>& array) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if (!BucketSort::sort(array)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        }

        return sortArray<int>(array);
    }

    // ===== wybór algorytmu dla listy jednokierunkowej =====

    template <typename T>
    bool sortSingleList(SingleList<T>& list) {
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

        std::cerr << "ERROR! Selected algorithm is not implemented for this data type.\n";
        return false;
    }

    bool sortSingleList(SingleList<int>& list) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if (!BucketSort::sort(list)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        }

        return sortSingleList<int>(list);
    }

    // ===== wybór algorytmu dla listy dwukierunkowej =====

    template <typename T>
    bool sortDoubleList(DoubleList<T>& list) {
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

        std::cerr << "ERROR! Selected algorithm is not implemented for this data type.\n";
        return false;
    }

    bool sortDoubleList(DoubleList<int>& list) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if (!BucketSort::sort(list)) {
                std::cerr << "ERROR! Bucket sort failed.\n";
                return false;
            }

            return true;
        }

        return sortDoubleList<int>(list);
    }

    // ===== wybór algorytmu dla stosu =====

    template <typename T>
    bool sortStack(Stack<T>& stack) {
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

        std::cerr << "ERROR! This algorithm is not implemented for Stack.\n";
        return false;
    }

    // ===== benchmark dla tablicy =====

    template <typename T>
    bool runArrayBenchmark(BenchmarkStats& stats) {
        Array<T> source(Parameters::structureSize);
        // tworzymy strukturę źródłową o zadanym rozmiarze

        if (source.getSize() != Parameters::structureSize) {
            std::cerr << "ERROR! Failed to allocate source array.\n";
            return false;
        }

        if (!fillArrayByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }
        // generujemy dane tylko raz, żeby każda iteracja startowała z tego samego układu

        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();
        // minTime - najlepszy wynik
        // maxTime - najgorszy wynik
        // sumTime - suma czasów potrzebna do wyliczenia średniej

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            Array<T>* testArray = RandomArrayGenerator::copyArray(source);
            // każda iteracja sortuje kopię danych źródłowych,
            // dzięki temu wszystkie pomiary są porównywalne

            if (testArray == nullptr) {
                std::cerr << "ERROR! Failed to copy source array.\n";
                return false;
            }

            auto start = std::chrono::steady_clock::now();
            // początek pomiaru - od tego miejsca liczymy tylko czas sortowania

            if (!sortArray(*testArray)) {
                delete testArray;
                return false;
            }

            auto end = std::chrono::steady_clock::now();
            // koniec pomiaru

            if (!SortingCheck::SortedAscend(*testArray)) {
                std::cerr << "ERROR! Array is not sorted correctly.\n";
                delete testArray;
                return false;
            }
            // po każdym sortowaniu sprawdzamy poprawność wyniku

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            // zamieniamy różnicę czasu na mikrosekundy

            if (elapsed < minTime) {
                minTime = elapsed;
            }

            if (elapsed > maxTime) {
                maxTime = elapsed;
            }

            sumTime += elapsed;

            std::cout << "iteration " << (iteration + 1) << " [us] = " << elapsed.count() << "\n";

            delete testArray;
        }

        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);
        // liczymy średnią jako double, żeby nie stracić części ułamkowej

        return true;
    }

    // ===== benchmark dla listy jednokierunkowej =====

    template <typename T>
    bool runSingleListBenchmark(BenchmarkStats& stats) {
        SingleList<T> source;
        // tworzymy pustą listę źródłową

        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(T{})) {
                std::cerr << "ERROR! Failed to create source single list.\n";
                return false;
            }
        }
        // najpierw budujemy strukturę o odpowiednim rozmiarze,
        // a dopiero potem wpisujemy do niej dane zgodne z wybranym rozkładem

        if (!fillSingleListByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }

        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            SingleList<T>* testList = RandomArrayGenerator::copySingleList(source);

            if (testList == nullptr) {
                std::cerr << "ERROR! Failed to copy source single list.\n";
                return false;
            }

            auto start = std::chrono::steady_clock::now();

            if (!sortSingleList(*testList)) {
                delete testList;
                return false;
            }

            auto end = std::chrono::steady_clock::now();

            if (!SortingCheck::SortedAscend(*testList)) {
                std::cerr << "ERROR! SingleList is not sorted correctly.\n";
                delete testList;
                return false;
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            if (elapsed < minTime) {
                minTime = elapsed;
            }

            if (elapsed > maxTime) {
                maxTime = elapsed;
            }

            sumTime += elapsed;

            std::cout << "iteration " << (iteration + 1) << " [us] = " << elapsed.count() << "\n";

            delete testList;
        }

        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    // ===== benchmark dla listy dwukierunkowej =====

    template <typename T>
    bool runDoubleListBenchmark(BenchmarkStats& stats) {
        DoubleList<T> source;
        // tworzymy pustą listę źródłową

        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(T{})) {
                std::cerr << "ERROR! Failed to create source double list.\n";
                return false;
            }
        }

        if (!fillDoubleListByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }

        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            DoubleList<T>* testList = RandomArrayGenerator::copyDoubleList(source);

            if (testList == nullptr) {
                std::cerr << "ERROR! Failed to copy source double list.\n";
                return false;
            }

            auto start = std::chrono::steady_clock::now();

            if (!sortDoubleList(*testList)) {
                delete testList;
                return false;
            }

            auto end = std::chrono::steady_clock::now();

            if (!SortingCheck::SortedAscend(*testList)) {
                std::cerr << "ERROR! DoubleList is not sorted correctly.\n";
                delete testList;
                return false;
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            if (elapsed < minTime) {
                minTime = elapsed;
            }

            if (elapsed > maxTime) {
                maxTime = elapsed;
            }

            sumTime += elapsed;

            std::cout << "iteration " << (iteration + 1) << " [us] = " << elapsed.count() << "\n";

            delete testList;
        }

        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    // ===== benchmark dla stosu =====

    template <typename T>
    bool runStackBenchmark(BenchmarkStats& stats) {
        Stack<T> source;
        // tworzymy pusty stos źródłowy

        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.push(T{})) {
                std::cerr << "ERROR! Failed to create source stack.\n";
                return false;
            }
        }

        if (!fillStackByDistribution(source)) {
            std::cerr << "ERROR! Failed to generate source data.\n";
            return false;
        }

        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            Stack<T>* testStack = RandomArrayGenerator::copyStack(source);

            if (testStack == nullptr) {
                std::cerr << "ERROR! Failed to copy source stack.\n";
                return false;
            }

            auto start = std::chrono::steady_clock::now();

            if (!sortStack(*testStack)) {
                delete testStack;
                return false;
            }

            auto end = std::chrono::steady_clock::now();

            if (!SortingCheck::SortedAscend(*testStack)) {
                std::cerr << "ERROR! Stack is not sorted correctly.\n";
                delete testStack;
                return false;
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            if (elapsed < minTime) {
                minTime = elapsed;
            }

            if (elapsed > maxTime) {
                maxTime = elapsed;
            }

            sumTime += elapsed;

            std::cout << "iteration " << (iteration + 1) << " [us] = " << elapsed.count() << "\n";

            delete testStack;
        }

        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

} // namespace

bool BenchmarkRunner::run(BenchmarkStats& stats) {
    // sprawdzamy podstawowe parametry benchmarku

    if (Parameters::structureSize <= 0) {
        std::cerr << "ERROR! structureSize must be greater than 0.\n";
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

    if (Parameters::iterations <= 0) {
        std::cerr << "ERROR! iterations must be greater than 0.\n";
        return false;
    }

    // ===== tablica =====

    if (Parameters::structure == Parameters::Structures::array) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runArrayBenchmark<int>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runArrayBenchmark<float>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runArrayBenchmark<double>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runArrayBenchmark<std::string>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runArrayBenchmark<unsigned int>(stats);
        }

        std::cerr << "ERROR! This data type is not implemented for Array.\n";
        return false;
    }

    // ===== lista jednokierunkowa =====

    if (Parameters::structure == Parameters::Structures::singleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runSingleListBenchmark<int>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runSingleListBenchmark<float>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runSingleListBenchmark<double>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runSingleListBenchmark<std::string>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runSingleListBenchmark<unsigned int>(stats);
        }

        std::cerr << "ERROR! This data type is not implemented for SingleList.\n";
        return false;
    }

    // ===== lista dwukierunkowa =====

    if (Parameters::structure == Parameters::Structures::doubleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runDoubleListBenchmark<int>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runDoubleListBenchmark<float>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runDoubleListBenchmark<double>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runDoubleListBenchmark<std::string>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runDoubleListBenchmark<unsigned int>(stats);
        }

        std::cerr << "ERROR! This data type is not implemented for DoubleList.\n";
        return false;
    }

    // ===== stos =====

    if (Parameters::structure == Parameters::Structures::stack) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            std::cerr << "ERROR! Bucket sort is not implemented for Stack.\n";
            return false;
        }

        if (Parameters::dataType == Parameters::DataTypes::typeInt) {
            return runStackBenchmark<int>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeFloat) {
            return runStackBenchmark<float>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeDouble) {
            return runStackBenchmark<double>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::typeString) {
            return runStackBenchmark<std::string>(stats);
        }

        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) {
            return runStackBenchmark<unsigned int>(stats);
        }

        std::cerr << "ERROR! This data type is not implemented for Stack.\n";
        return false;
    }

    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}