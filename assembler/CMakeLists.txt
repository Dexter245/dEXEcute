cmake_minimum_required(VERSION 2.8.11)
project(dEXEcute)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -pedantic-errors -Wall -Werror")

set(SOURCE_FILES_ASSEMBLER
    src/assembler.cpp
    src/dconst.cpp
    src/main.cpp
    )

add_executable("assembler" ${SOURCE_FILES_ASSEMBLER})

set(SOURCE_FILES_ASSEMBLER_TEST
    src/assembler.cpp
    src/dconst.cpp
    src/test/assemblerTester.cpp
    src/test/main_test.cpp
    )

add_executable(assembler_test ${SOURCE_FILES_ASSEMBLER_TEST})



