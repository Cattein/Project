//
// Created by MashaGuzhva on 12/04/2026.
//

#include "benchmark/BenchmarkCsvWriter.h"

#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>

#include "Parameters.h"

static std::string algorithmToString(Parameters::Algorithms algorithm) {
    if (algorithm == Parameters::Algorithms::quick) {
        return "quick";
    }
    if (algorithm == Parameters::Algorithms::shell) {
        return "shell";
    }
    if (algorithm == Parameters::Algorithms::bucket) {
        return "bucket";
    }

    return "undefined";
}

static std::string structureToString(Parameters::Structures structure) {
    if (structure == Parameters::Structures::array) {
        return "array";
    }
    if (structure == Parameters::Structures::singleList) {
        return "singleList";
    }
    if (structure == Parameters::Structures::doubleList) {
        return "doubleList";
    }
    if (structure == Parameters::Structures::queue) {
        return "queue";
    }
    if (structure == Parameters::Structures::stack) {
        return "stack";
    }
    if (structure == Parameters::Structures::binaryTree) {
        return "binaryTree";
    }

    return "undefined";
}

static std::string dataTypeToString(Parameters::DataTypes dataType) {
    if (dataType == Parameters::DataTypes::typeInt) {
        return "int";
    }
    if (dataType == Parameters::DataTypes::typeFloat) {
        return "float";
    }
    if (dataType == Parameters::DataTypes::typeDouble) {
        return "double";
    }
    if (dataType == Parameters::DataTypes::typeChar) {
        return "char";
    }
    if (dataType == Parameters::DataTypes::typeString) {
        return "string";
    }
    if (dataType == Parameters::DataTypes::typeUnsignedInt) {
        return "unsignedInt";
    }
    if (dataType == Parameters::DataTypes::typeUnsignedLong) {
        return "unsignedLong";
    }
    if (dataType == Parameters::DataTypes::typeUnsignedChar) {
        return "unsignedChar";
    }

    return "undefined";
}

static std::string pivotToString(Parameters::Pivots pivot) {
    if (pivot == Parameters::Pivots::random) {
        return "random";
    }
    if (pivot == Parameters::Pivots::middle) {
        return "middle";
    }
    if (pivot == Parameters::Pivots::left || pivot == Parameters::Pivots::right) {
        return "edge";
    }

    return "undefined";
}

static std::string shellParameterToString(Parameters::ShellParameters parameter) {
    if (parameter == Parameters::ShellParameters::option1) {
        return "option1";
    }
    if (parameter == Parameters::ShellParameters::option2) {
        return "option2";
    }
    return "undefined";
}

bool BenchmarkCsvWriter::appendResult(const std::string& filename, const BenchmarkStats& stats) {
    if (filename.empty()) {
        return false;
    }

    bool writeHeader = false;

    {
        std::ifstream checkFile(filename);
        if (!checkFile.good() || checkFile.peek() == std::ifstream::traits_type::eof()) {
            writeHeader = true;
        }
    }

    std::ofstream file(filename, std::ios::app);
    if (!file) {
        return false;
    }

    if (writeHeader) {
        file << "timestamp,algorithm,structure,dataType,size,iterations,pivot,shellParameter,min_us,max_us,avg_us\n";
    }

    const auto now = std::chrono::system_clock::now();
    const std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

    file << std::put_time(std::localtime(&nowTime), "%Y-%m-%d %H:%M:%S") << ","
         << algorithmToString(Parameters::algorithm) << ","
         << structureToString(Parameters::structure) << ","
         << dataTypeToString(Parameters::dataType) << ","
         << Parameters::structureSize << ","
         << Parameters::iterations << ","
         << pivotToString(Parameters::pivot) << ","
         << shellParameterToString(Parameters::shellParameter) << ","
         << stats.minTimeFinal << ","
         << stats.maxTimeFinal << ","
         << std::fixed << std::setprecision(2) << stats.averageTimeFinal
         << "\n";

    return true;
}



