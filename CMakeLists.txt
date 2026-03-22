cmake_minimum_required(VERSION 3.31.6)
project(Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# lokalizacji przechowywania plików
set(PROG_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROG_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PROG_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/lib")


#dodaje ścieżkę do katalogu dla wszystkich projektów
include_directories(${PROG_INCLUDE})

add_executable(Project src/main.cpp)

target_compile_options(Project PRIVATE -Wall -Wextra -Werror)


