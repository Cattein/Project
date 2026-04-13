cmake_minimum_required(VERSION 3.31.6)
project(Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# lokalizacje przechowywania plików
set(PROG_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROG_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PROG_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_executable(Project
        src/main.cpp
        include/structures/Array.h
        include/structures/SingleList.h
        include/structures/DoubleList.h
        lib/parameters/Parameters.cpp
        src/file/FileHandler.cpp
        src/algorytmsSorting/QuickSort.cpp
        include/checking/sortingCheck.h
        src/algorytmsSorting/ShellSort.cpp
        src/algorytmsSorting/BucketSort.cpp
        src/singleFile/SingleFileRunner.cpp
        src/benchmark/RandomArrayGenerator.cpp
        src/benchmark/BenchmarkRunner.cpp
        src/benchmark/BenchmarkCsvWriter.cpp
)

target_include_directories(Project PUBLIC
        ${PROG_INCLUDE}
        ${PROG_LIBS}/parameters
)

target_compile_options(Project PRIVATE
        -Wall
        -Wextra
        -Werror
)