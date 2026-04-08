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
        ${PROG_SRC}/main.cpp
        ${PROG_SRC}/structures/Array.cpp
        ${PROG_SRC}/structures/Singlelist.cpp
        ${PROG_LIBS}/parameters/Parameters.cpp
        include/structures/DoubleList.h
        src/structures/DoubleList.cpp
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