cmake_minimum_required(VERSION 3.17)
project(easy_compiler)

set(CMAKE_CXX_STANDARD 14)

# easy_compiler src
file(GLOB EASY_COMPILER_SRC
        main.cpp
        src/*.cpp)

# easy_compiler include
include_directories(inc)

add_executable(easy_compiler ${EASY_COMPILER_SRC})

add_subdirectory(tests)
