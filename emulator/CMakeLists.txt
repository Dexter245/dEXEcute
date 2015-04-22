cmake_minimum_required(VERSION 2.8.11)
project(dEXEcute)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -pedantic-errors -Wall -Werror")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)


set(SOURCE_FILES_EMULATOR
    src/main.cpp
    src/mainwindow.cpp
    )

add_executable(emulator ${SOURCE_FILES_EMULATOR})

# Use the Widgets module from Qt 5.
target_link_libraries(emulator Qt5::Widgets)




