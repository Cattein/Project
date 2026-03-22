cmake_minimum_required(VERSION 3.31.6)
project(Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# lokalizacji przechowywania plików
set(PROG_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROG_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PROG_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_executable(Project src/main.cpp
        src/structures/Array.cpp
        include/structures/Array.h)


#dodaje ścieżkę do katalogu dla wszystkich projektów
target_include_directories(Project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(Project ${CMAKE_CURRENT_SOURCE_DIR}/lib/libhelloparams.so)


set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_COMPILER "g++")


