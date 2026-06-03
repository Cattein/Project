//
// Created by MashaGuzhva on 12/04/2026.
//

#include "benchmark/BenchmarkRunner.h"

#include <iostream>
#include <chrono>
#include <string>
#include <type_traits>

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
    // w projekcie zaimplementowano tylko option1 i option2
    bool isShellParameterSupported() {
        return Parameters::shellParameter != Parameters::ShellParameters::option3 &&
               Parameters::shellParameter != Parameters::ShellParameters::option4;
    }

    // wypełnia strukturę zgodnie z rozkładem wybranym w parametrach
    // ta funkcja jest wspólna dla wszystkich struktur danych
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

        // jeśli parametr distribution nie pasuje do żadnego poprawnego wariantu
        return false;
    }

    // ===== tworzenie struktur =====
    // poniższe funkcje przygotowują pustą strukturę o zadanym rozmiarze
    // dzięki temu później można ją wypełnić odpowiednimi danymi testowymi

    template <typename T>
    bool createSource(Array<T>& source) {
        // tablica ma już ustalony rozmiar po konstruktorze
        return source.getSize() == Parameters::structureSize;
    }

    template <typename T>
    bool createSource(SingleList<T>& source) {
        // lista startuje jako pusta, więc trzeba ręcznie dodać odpowiednią liczbę elementów
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(T{})) {
                return false;
            }
        }

        // jeśli wszystkie elementy zostały dodane, tworzenie się udało
        return true;
    }

    template <typename T>
    bool createSource(DoubleList<T>& source) {
        // analogicznie jak dla listy jednokierunkowej
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(T{})) {
                return false;
            }
        }

        // jeśli wszystkie elementy zostały dodane, tworzenie się udało
        return true;
    }

    template <typename T>
    bool createSource(Stack<T>& source) {
        // stos budujemy przez kolejne dodawanie elementów na szczyt
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.push(T{})) {
                return false;
            }
        }

        // jeśli wszystkie elementy zostały dodane, tworzenie się udało
        return true;
    }

    template <typename T>
    bool createSource(BinaryTree<T>& source) {
        // drzewo wypełniamy poziomami przez pushBack
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(T{})) {
                return false;
            }
        }

        // jeśli wszystkie elementy zostały dodane, tworzenie się udało
        return true;
    }

    // ===== wybór algorytmu sortowania =====
    // poniższe funkcje uruchamiają właściwy algorytm zależnie od parametrów programu

    template <typename T>
    bool sortStructure(Array<T>& array) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if constexpr ((std::is_arithmetic<T>::value || std::is_same<T, std::string>::value)) {
                if (!BucketSort::sort(array)) {
                    std::cerr << "ERROR! Bucket sort failed.\n";
                    return false;
                }

                return true;
            } else {
                std::cerr << "ERROR! Bucket sort works only for arithmetic data types and std::string.\n";
                return false;
            }
        }

        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            // uruchamiamy quicksort z wybranym sposobem wyboru pivota
            QuickSort::sort(array, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            // najpierw sprawdzamy, czy wybrany wariant shellsorta jest dostępny
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            // uruchamiamy shellsort dla tablicy
            ShellSort::sort(array, Parameters::shellParameter);
            return true;
        }

        // jeśli program trafił tutaj, to dla tej struktury algorytm nie jest obsługiwany
        std::cerr << "ERROR! Selected algorithm is not implemented for Array.\n";
        return false;
    }

    template <typename T>
    bool sortStructure(SingleList<T>& list) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if constexpr ((std::is_arithmetic<T>::value || std::is_same<T, std::string>::value)) {
                if (!BucketSort::sort(list)) {
                    std::cerr << "ERROR! Bucket sort failed.\n";
                    return false;
                }

                return true;
            } else {
                std::cerr << "ERROR! Bucket sort works only for arithmetic data types and std::string.\n";
                return false;
            }
        }

        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            // uruchamiamy quicksort dla listy jednokierunkowej
            QuickSort::sort(list, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            // sprawdzamy, czy wybrany wariant shellsorta jest obsługiwany
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            // uruchamiamy shellsort dla listy jednokierunkowej
            ShellSort::sort(list, Parameters::shellParameter);
            return true;
        }

        // jeśli program trafił tutaj, to dla tej struktury algorytm nie jest obsługiwany
        std::cerr << "ERROR! Selected algorithm is not implemented for SingleList.\n";
        return false;
    }

    template <typename T>
    bool sortStructure(DoubleList<T>& list) {
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            if constexpr ((std::is_arithmetic<T>::value || std::is_same<T, std::string>::value)) {
                if (!BucketSort::sort(list)) {
                    std::cerr << "ERROR! Bucket sort failed.\n";
                    return false;
                }

                return true;
            } else {
                std::cerr << "ERROR! Bucket sort works only for arithmetic data types and std::string.\n";
                return false;
            }
        }

        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            // uruchamiamy quicksort dla listy dwukierunkowej
            QuickSort::sort(list, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            // sprawdzamy, czy wybrany wariant shellsorta jest obsługiwany
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            // uruchamiamy shellsort dla listy dwukierunkowej
            ShellSort::sort(list, Parameters::shellParameter);
            return true;
        }

        // jeśli program trafił tutaj, to dla tej struktury algorytm nie jest obsługiwany
        std::cerr << "ERROR! Selected algorithm is not implemented for DoubleList.\n";
        return false;
    }

    template <typename T>
    bool sortStructure(Stack<T>& stack) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            // uruchamiamy quicksort dla stosu
            QuickSort::sort(stack, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            // sprawdzamy, czy wybrany wariant shellsorta jest obsługiwany
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            // uruchamiamy shellsort dla stosu
            ShellSort::sort(stack, Parameters::shellParameter);
            return true;
        }

        // Bucket Sort nie został zaimplementowany dla stosu
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            std::cerr << "ERROR! Bucket sort is not implemented for Stack.\n";
            return false;
        }

        // jeśli program trafił tutaj, to dla tej struktury algorytm nie jest obsługiwany
        std::cerr << "ERROR! Selected algorithm is not implemented for Stack.\n";
        return false;
    }

    template <typename T>
    bool sortStructure(BinaryTree<T>& tree) {
        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            // uruchamiamy quicksort dla drzewa
            QuickSort::sort(tree, Parameters::pivot);
            return true;
        }

        if (Parameters::algorithm == Parameters::Algorithms::shell) {
            // sprawdzamy, czy wybrany wariant shellsorta jest obsługiwany
            if (!isShellParameterSupported()) {
                std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                return false;
            }

            // uruchamiamy shellsort dla drzewa
            ShellSort::sort(tree, Parameters::shellParameter);
            return true;
        }

        // Bucket Sort nie został zaimplementowany dla drzewa
        if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            std::cerr << "ERROR! Bucket sort is not implemented for BinaryTree.\n";
            return false;
        }

        // jeśli program trafił tutaj, to dla tej struktury algorytm nie jest obsługiwany
        std::cerr << "ERROR! Selected algorithm is not implemented for BinaryTree.\n";
        return false;
    }

    // ===== pomocnicze funkcje benchmarku =====

    // aktualizuje końcowe statystyki czasu:
    // minimum, maksimum oraz sumę wszystkich czasów
    void updateTimeStats(const std::chrono::microseconds elapsed,
                         std::chrono::microseconds& minTime,
                         std::chrono::microseconds& maxTime,
                         std::chrono::microseconds& sumTime) {
        // jeśli obecny wynik jest mniejszy od dotychczasowego minimum, zapisujemy go
        if (elapsed < minTime) {
            minTime = elapsed;
        }

        // jeśli obecny wynik jest większy od dotychczasowego maksimum, zapisujemy go
        if (elapsed > maxTime) {
            maxTime = elapsed;
        }

        // suma będzie potem użyta do obliczenia średniego czasu
        sumTime += elapsed;
    }

    // wykonuje pojedynczy pomiar:
    // 1. sortuje strukturę
    // 2. sprawdza poprawność wyniku
    // 3. zwraca czas sortowania
    template <typename Structure>
    bool measureSingleIteration(Structure& testStructure,
                                const std::string& structureName,
                                std::chrono::microseconds& elapsed) {
        // start pomiaru czasu - od tego momentu mierzymy już tylko samo sortowanie
        const auto start = std::chrono::steady_clock::now();

        if (!sortStructure(testStructure)) {
            return false;
        }

        // koniec pomiaru czasu - po zakończeniu sortowania
        const auto end = std::chrono::steady_clock::now();

        // sprawdzamy, czy algorytm rzeczywiście zwrócił dane w porządku rosnącym
        if (!SortingCheck::SortedAscend(testStructure)) {
            std::cerr << "ERROR! " << structureName << " is not sorted correctly.\n";
            return false;
        }

        // przeliczamy zmierzony odcinek czasu na mikrosekundy
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return true;
    }

    // ===== benchmark dla konkretnych struktur =====
    // każda iteracja:
    // 1. tworzy nową strukturę
    // 2. wypełnia ją zgodnie z wybranym rozkładem
    // 3. mierzy czas sortowania
    // 4. sprawdza poprawność wyniku
    // 5. aktualizuje min, max i średnią
    //
    // ważne:
    // dane są przygotowywane od nowa przed każdą iteracją,
    // dzięki czemu dla rozkładu random każda iteracja dostaje nowe dane losowe

    template <typename T>
    bool runArrayBenchmark(BenchmarkStats& stats) {
        // na początku ustawiamy wartości pomocnicze do statystyk
        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy nową tablicę dla bieżącej iteracji
            Array<T> testStructure(Parameters::structureSize);

            if (!createSource(testStructure)) {
                std::cerr << "ERROR! Failed to create source array.\n";
                return false;
            }

            // przygotowujemy nowe dane wejściowe zgodnie z wybranym rozkładem
            if (!fillByDistribution(testStructure)) {
                std::cerr << "ERROR! Failed to generate source data.\n";
                return false;
            }

            // zmienna elapsed będzie przechowywać czas tej iteracji
            std::chrono::microseconds elapsed{};

            if (!measureSingleIteration(testStructure, "Array", elapsed)) {
                return false;
            }

            // po udanym pomiarze aktualizujemy statystyki czasu
            updateTimeStats(elapsed, minTime, maxTime, sumTime);

            // wypisujemy czas pojedynczej iteracji
            std::cout << "iteration " << (iteration + 1)
                      << " [us] = " << elapsed.count() << "\n";
        }

        // zapisujemy końcowe statystyki do struktury wynikowej
        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    template <typename T>
    bool runSingleListBenchmark(BenchmarkStats& stats) {
        // na początku ustawiamy wartości pomocnicze do statystyk
        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy nową listę jednokierunkową dla bieżącej iteracji
            SingleList<T> testStructure;

            if (!createSource(testStructure)) {
                std::cerr << "ERROR! Failed to create source single list.\n";
                return false;
            }

            // przygotowujemy nowe dane wejściowe zgodnie z wybranym rozkładem
            if (!fillByDistribution(testStructure)) {
                std::cerr << "ERROR! Failed to generate source data.\n";
                return false;
            }

            // zmienna elapsed będzie przechowywać czas tej iteracji
            std::chrono::microseconds elapsed{};

            if (!measureSingleIteration(testStructure, "SingleList", elapsed)) {
                return false;
            }

            // po udanym pomiarze aktualizujemy statystyki czasu
            updateTimeStats(elapsed, minTime, maxTime, sumTime);

            // wypisujemy czas pojedynczej iteracji
            std::cout << "iteration " << (iteration + 1)
                      << " [us] = " << elapsed.count() << "\n";
        }

        // zapisujemy końcowe statystyki do struktury wynikowej
        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    template <typename T>
    bool runDoubleListBenchmark(BenchmarkStats& stats) {
        // na początku ustawiamy wartości pomocnicze do statystyk
        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy nową listę dwukierunkową dla bieżącej iteracji
            DoubleList<T> testStructure;

            if (!createSource(testStructure)) {
                std::cerr << "ERROR! Failed to create source double list.\n";
                return false;
            }

            // przygotowujemy nowe dane wejściowe zgodnie z wybranym rozkładem
            if (!fillByDistribution(testStructure)) {
                std::cerr << "ERROR! Failed to generate source data.\n";
                return false;
            }

            // zmienna elapsed będzie przechowywać czas tej iteracji
            std::chrono::microseconds elapsed{};

            if (!measureSingleIteration(testStructure, "DoubleList", elapsed)) {
                return false;
            }

            // po udanym pomiarze aktualizujemy statystyki czasu
            updateTimeStats(elapsed, minTime, maxTime, sumTime);

            // wypisujemy czas pojedynczej iteracji
            std::cout << "iteration " << (iteration + 1)
                      << " [us] = " << elapsed.count() << "\n";
        }

        // zapisujemy końcowe statystyki do struktury wynikowej
        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    template <typename T>
    bool runStackBenchmark(BenchmarkStats& stats) {
        // na początku ustawiamy wartości pomocnicze do statystyk
        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy nowy stos dla bieżącej iteracji
            Stack<T> testStructure;

            if (!createSource(testStructure)) {
                std::cerr << "ERROR! Failed to create source stack.\n";
                return false;
            }

            // przygotowujemy nowe dane wejściowe zgodnie z wybranym rozkładem
            if (!fillByDistribution(testStructure)) {
                std::cerr << "ERROR! Failed to generate source data.\n";
                return false;
            }

            // zmienna elapsed będzie przechowywać czas tej iteracji
            std::chrono::microseconds elapsed{};

            if (!measureSingleIteration(testStructure, "Stack", elapsed)) {
                return false;
            }

            // po udanym pomiarze aktualizujemy statystyki czasu
            updateTimeStats(elapsed, minTime, maxTime, sumTime);

            // wypisujemy czas pojedynczej iteracji
            std::cout << "iteration " << (iteration + 1)
                      << " [us] = " << elapsed.count() << "\n";
        }

        // zapisujemy końcowe statystyki do struktury wynikowej
        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    template <typename T>
    bool runBinaryTreeBenchmark(BenchmarkStats& stats) {
        // na początku ustawiamy wartości pomocnicze do statystyk
        auto minTime = std::chrono::microseconds::max();
        auto maxTime = std::chrono::microseconds::zero();
        auto sumTime = std::chrono::microseconds::zero();

        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy nowe drzewo binarne dla bieżącej iteracji
            BinaryTree<T> testStructure;

            if (!createSource(testStructure)) {
                std::cerr << "ERROR! Failed to create source binary tree.\n";
                return false;
            }

            // przygotowujemy nowe dane wejściowe zgodnie z wybranym rozkładem
            if (!fillByDistribution(testStructure)) {
                std::cerr << "ERROR! Failed to generate source data.\n";
                return false;
            }

            // zmienna elapsed będzie przechowywać czas tej iteracji
            std::chrono::microseconds elapsed{};

            if (!measureSingleIteration(testStructure, "BinaryTree", elapsed)) {
                return false;
            }

            // po udanym pomiarze aktualizujemy statystyki czasu
            updateTimeStats(elapsed, minTime, maxTime, sumTime);

            // wypisujemy czas pojedynczej iteracji
            std::cout << "iteration " << (iteration + 1)
                      << " [us] = " << elapsed.count() << "\n";
        }

        // zapisujemy końcowe statystyki do struktury wynikowej
        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
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

    // quicksort wymaga zdefiniowanego pivota
    if (Parameters::algorithm == Parameters::Algorithms::quick &&
        Parameters::pivot == Parameters::Pivots::undefined) {
        std::cerr << "ERROR! pivot must be set for quick sort.\n";
        return false;
    }

    // shellsort wymaga zdefiniowanego wariantu odstępów
    if (Parameters::algorithm == Parameters::Algorithms::shell &&
        Parameters::shellParameter == Parameters::ShellParameters::undefined) {
        std::cerr << "ERROR! shellParameter must be set for shell sort.\n";
        return false;
    }

    // ===== array =====
    // wybieramy odpowiedni typ danych dla tablicy

    if (Parameters::structure == Parameters::Structures::array) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runArrayBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runArrayBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runArrayBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runArrayBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runArrayBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runArrayBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runArrayBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runArrayBenchmark<unsigned char>(stats);

        // jeśli typ danych nie został obsłużony, zwracamy błąd
        std::cerr << "ERROR! This data type is not implemented for Array.\n";
        return false;
    }

    // ===== single list =====
    // wybieramy odpowiedni typ danych dla listy jednokierunkowej

    if (Parameters::structure == Parameters::Structures::singleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runSingleListBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runSingleListBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runSingleListBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runSingleListBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runSingleListBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runSingleListBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runSingleListBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runSingleListBenchmark<unsigned char>(stats);

        // jeśli typ danych nie został obsłużony, zwracamy błąd
        std::cerr << "ERROR! This data type is not implemented for SingleList.\n";
        return false;
    }

    // ===== double list =====
    // wybieramy odpowiedni typ danych dla listy dwukierunkowej

    if (Parameters::structure == Parameters::Structures::doubleList) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runDoubleListBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runDoubleListBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runDoubleListBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runDoubleListBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runDoubleListBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runDoubleListBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runDoubleListBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runDoubleListBenchmark<unsigned char>(stats);

        // jeśli typ danych nie został obsłużony, zwracamy błąd
        std::cerr << "ERROR! This data type is not implemented for DoubleList.\n";
        return false;
    }

    // ===== stack =====
    // wybieramy odpowiedni typ danych dla stosu

    if (Parameters::structure == Parameters::Structures::stack) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runStackBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runStackBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runStackBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runStackBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runStackBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runStackBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runStackBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runStackBenchmark<unsigned char>(stats);

        // jeśli typ danych nie został obsłużony, zwracamy błąd
        std::cerr << "ERROR! This data type is not implemented for Stack.\n";
        return false;
    }

    // ===== binary tree =====
    // wybieramy odpowiedni typ danych dla drzewa binarnego

    if (Parameters::structure == Parameters::Structures::binaryTree) {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) return runBinaryTreeBenchmark<int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeFloat) return runBinaryTreeBenchmark<float>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeDouble) return runBinaryTreeBenchmark<double>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeChar) return runBinaryTreeBenchmark<char>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeString) return runBinaryTreeBenchmark<std::string>(stats);
        if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) return runBinaryTreeBenchmark<unsigned int>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) return runBinaryTreeBenchmark<unsigned long>(stats);
        if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) return runBinaryTreeBenchmark<unsigned char>(stats);

        // jeśli typ danych nie został obsłużony, zwracamy błąd
        std::cerr << "ERROR! This data type is not implemented for BinaryTree.\n";
        return false;
    }

    // jeśli żadna struktura nie pasuje, to znaczy że nie została zaimplementowana
    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}