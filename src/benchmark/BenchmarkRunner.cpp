//
// Created by MashaGuzhva on 12/04/2026.
//

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

bool BenchmarkRunner::run(BenchmarkStats& stats) {

    // rozmiar tablicy do testu musi być większy od 0
    if (Parameters::structureSize <= 0) {
        std::cerr << "ERROR! structureSize must be greater than 0.\n";
        return false;
    }

    // liczba powtórzeń benchmarku musi być większa od 0
    if (Parameters::iterations <= 0) {
        std::cerr << "ERROR! iterations must be greater than 0.\n";
        return false;
    }

    // ustawiamy minTime na max możliwą wartość - 1 prawdziwy pomiar na pewno będzie mniejszy
    auto minTime = std::chrono::microseconds::max();

    // ustawiamy maxTime na 0
    auto maxTime = std::chrono::microseconds::zero();

    // suma dla średniej
    auto sumTime = std::chrono::microseconds::zero();

    // ===== ARRAY =====
    if (Parameters::structure == Parameters::Structures::array) {
        // tablica źródłowa
        Array source(Parameters::structureSize);

        // wypełniamy tablicę losowymi liczbami
        if (!RandomArrayGenerator::fillRandom(source)) {
            std::cerr << "ERROR! Failed to generate random data.\n";
            return false;
        }

        // wykonujemy benchmark tyle razy, ile podano w iterations
        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy kopię tablicy źródłowej
            Array* testArray = RandomArrayGenerator::copyArray(source);

            // jeśli nie udało się zrobić kopii, kończymy z błędem
            if (testArray == nullptr) {
                std::cerr << "ERROR! Failed to copy source array.\n";
                return false;
            }

            // zapisujemy moment startu sortowania
            auto start = std::chrono::steady_clock::now();
            // auto oznacza, że kompilator sam dobierze odpowiedni typ

            // wybieramy algorytm sortowania zależnie od parametrów
            if (Parameters::algorithm == Parameters::Algorithms::quick) {
                QuickSort::sort(*testArray, Parameters::pivot);
            }
            else if (Parameters::algorithm == Parameters::Algorithms::shell) {
                // na razie obsługiwane są tylko option1 i option2
                if (Parameters::shellParameter == Parameters::ShellParameters::option3 ||
                    Parameters::shellParameter == Parameters::ShellParameters::option4) {
                    std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                    delete testArray;
                    return false;
                }

                ShellSort::sort(*testArray, Parameters::shellParameter);
            }
            else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
                // bucket sort zwraca bool, więc sprawdzamy czy sortowanie się udało
                if (!BucketSort::sort(*testArray)) {
                    std::cerr << "ERROR! Bucket sort failed.\n";
                    delete testArray;
                    return false;
                }
            }
            else {
                // jeśli wybrany algorytm nie jest jeszcze gotowy, kończymy z błędem
                std::cerr << "ERROR! Selected algorithm is not implemented.\n";
                delete testArray;
                return false;
            }

            // zapisujemy moment końca sortowania
            auto end = std::chrono::steady_clock::now();
            // auto oznacza, że kompilator sam dobierze odpowiedni typ

            // sprawdzamy, czy po sortowaniu tablica jest naprawdę rosnąca
            if (!SortingCheck::SortedAscend(*testArray)) {
                std::cerr << "ERROR! Array is not sorted correctly.\n";
                delete testArray;
                return false;
            }

            // czas działania jednej iteracji w mikrosekundach
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            // jeśli aktualny czas jest mniejszy niż dotychczasowe minimum
            // zapisujemy go jako nowy najlepszy wynik
            if (elapsed < minTime) {
                minTime = elapsed;
            }

            // jeśli aktualny czas jest większy niż dotychczasowe maksimum
            // zapisujemy go jako nowy najgorszy wynik
            if (elapsed > maxTime) {
                maxTime = elapsed;
            }

            sumTime += elapsed;

            // wypisujemy czas dla aktualnej iteracji
            std::cout << "iteration " << (iteration + 1) << " [us] = " << elapsed.count() << "\n";

            delete testArray;
            // po zakończeniu iteracji usuwamy kopię tablicy z pamięci
        }

        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    // ===== SINGLE LIST =====
    if (Parameters::structure == Parameters::Structures::singleList) {
        SingleList source;
        // tworzymy pustą listę źródłową

        // najpierw dodajemy elementy do listy, żeby miała odpowiedni rozmiar
        // potem fillRandom będzie mogło wpisywać liczby pod kolejne indeksy
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(0)) {
                std::cerr << "ERROR! Failed to create source single list.\n";
                return false;
            }
        }

        // wypełniamy listę losowymi liczbami
        if (!RandomArrayGenerator::fillRandom(source)) {
            std::cerr << "ERROR! Failed to generate random data.\n";
            return false;
        }

        // wykonujemy benchmark tyle razy, ile podano w iterations
        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy kopię listy źródłowej
            SingleList* testList = RandomArrayGenerator::copySingleList(source);

            // jeśli nie udało się zrobić kopii, kończymy z błędem
            if (testList == nullptr) {
                std::cerr << "ERROR! Failed to copy source single list.\n";
                return false;
            }

            // zapisujemy moment startu sortowania
            auto start = std::chrono::steady_clock::now();
            // auto oznacza, że kompilator sam dobierze odpowiedni typ

            // wybieramy algorytm sortowania zależnie od parametrów
            if (Parameters::algorithm == Parameters::Algorithms::quick) {
                QuickSort::sort(*testList, Parameters::pivot);
            }
            else if (Parameters::algorithm == Parameters::Algorithms::shell) {
                // na razie obsługiwane są tylko option1 i option2
                if (Parameters::shellParameter == Parameters::ShellParameters::option3 ||
                    Parameters::shellParameter == Parameters::ShellParameters::option4) {
                    std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                    delete testList;
                    return false;
                }

                ShellSort::sort(*testList, Parameters::shellParameter);
            }
            else {
                // pozostałe algorytmy nie są jeszcze gotowe dla singlelist
                std::cerr << "ERROR! This algorithm is not implemented for SingleList yet.\n";
                delete testList;
                return false;
            }

            // zapisujemy moment końca sortowania
            auto end = std::chrono::steady_clock::now();
            // auto oznacza, że kompilator sam dobierze odpowiedni typ

            // sprawdzamy, czy po sortowaniu lista jest naprawdę rosnąca
            if (!SortingCheck::SortedAscend(*testList)) {
                std::cerr << "ERROR! SingleList is not sorted correctly.\n";
                delete testList;
                return false;
            }

            // czas działania jednej iteracji w mikrosekundach
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            // jeśli aktualny czas jest mniejszy niż dotychczasowe minimum
            // zapisujemy go jako nowy najlepszy wynik
            if (elapsed < minTime) {
                minTime = elapsed;
            }

            // jeśli aktualny czas jest większy niż dotychczasowe maksimum
            // zapisujemy go jako nowy najgorszy wynik
            if (elapsed > maxTime) {
                maxTime = elapsed;
            }

            sumTime += elapsed;

            // wypisujemy czas dla aktualnej iteracji
            std::cout << "iteration " << (iteration + 1) << " [us] = " << elapsed.count() << "\n";

            delete testList;
            // po zakończeniu iteracji usuwamy kopię listy z pamięci
        }

        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    // ===== DOUBLE LIST =====
    if (Parameters::structure == Parameters::Structures::doubleList) {
        DoubleList source;
        // tworzymy pustą listę dwukierunkową źródłową

        // najpierw dodajemy elementy do listy, żeby miała odpowiedni rozmiar
        // potem fillRandom będzie mogło wpisywać liczby pod kolejne indeksy
        for (int i = 0; i < Parameters::structureSize; ++i) {
            if (!source.pushBack(0)) {
                std::cerr << "ERROR! Failed to create source double list.\n";
                return false;
            }
        }

        // wypełniamy listę losowymi liczbami
        if (!RandomArrayGenerator::fillRandom(source)) {
            std::cerr << "ERROR! Failed to generate random data.\n";
            return false;
        }

        // wykonujemy benchmark tyle razy, ile podano w iterations
        for (int iteration = 0; iteration < Parameters::iterations; ++iteration) {
            // tworzymy kopię listy źródłowej
            DoubleList* testList = RandomArrayGenerator::copyDoubleList(source);

            // jeśli nie udało się zrobić kopii, kończymy z błędem
            if (testList == nullptr) {
                std::cerr << "ERROR! Failed to copy source double list.\n";
                return false;
            }

            // zapisujemy moment startu sortowania
            auto start = std::chrono::steady_clock::now();
            // auto oznacza, że kompilator sam dobierze odpowiedni typ

            // wybieramy algorytm sortowania zależnie od parametrów
            if (Parameters::algorithm == Parameters::Algorithms::quick) {
                QuickSort::sort(*testList, Parameters::pivot);
            }
            else if (Parameters::algorithm == Parameters::Algorithms::shell) {
                // na razie obsługiwane są tylko option1 i option2
                if (Parameters::shellParameter == Parameters::ShellParameters::option3 ||
                    Parameters::shellParameter == Parameters::ShellParameters::option4) {
                    std::cerr << "ERROR! Only shell parameters option1 and option2 are supported now.\n";
                    delete testList;
                    return false;
                }

                ShellSort::sort(*testList, Parameters::shellParameter);
            }
            else {
                // pozostałe algorytmy nie są jeszcze gotowe dla doublelist
                std::cerr << "ERROR! This algorithm is not implemented for DoubleList yet.\n";
                delete testList;
                return false;
            }

            // zapisujemy moment końca sortowania
            auto end = std::chrono::steady_clock::now();
            // auto oznacza, że kompilator sam dobierze odpowiedni typ

            // sprawdzamy, czy po sortowaniu lista jest naprawdę rosnąca
            if (!SortingCheck::SortedAscend(*testList)) {
                std::cerr << "ERROR! DoubleList is not sorted correctly.\n";
                delete testList;
                return false;
            }

            // czas działania jednej iteracji w mikrosekundach
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            // jeśli aktualny czas jest mniejszy niż dotychczasowe minimum
            // zapisujemy go jako nowy najlepszy wynik
            if (elapsed < minTime) {
                minTime = elapsed;
            }

            // jeśli aktualny czas jest większy niż dotychczasowe maksimum
            // zapisujemy go jako nowy najgorszy wynik
            if (elapsed > maxTime) {
                maxTime = elapsed;
            }

            sumTime += elapsed;

            // wypisujemy czas dla aktualnej iteracji
            std::cout << "iteration " << (iteration + 1) << " [us] = " << elapsed.count() << "\n";

            delete testList;
            // po zakończeniu iteracji usuwamy kopię listy z pamięci
        }

        stats.minTimeFinal = minTime.count();
        stats.maxTimeFinal = maxTime.count();
        stats.averageTimeFinal =
            static_cast<double>(sumTime.count()) / static_cast<double>(Parameters::iterations);

        return true;
    }

    std::cerr << "ERROR! This structure is not implemented yet.\n";
    return false;
}