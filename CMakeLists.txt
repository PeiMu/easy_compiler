cmake_minimum_required(VERSION 3.17)
project(easy_compiler)

set(CMAKE_CXX_STANDARD 14)

# easy_compiler src
file(GLOB EASY_COMPILER_SRC
        main.cpp
        src/*.cpp)

set(CXX_FLAGS
        -Wall
        -Werror
        -g
        -O2)

# easy_compiler include
include_directories(inc)

add_executable(easy_compiler ${EASY_COMPILER_SRC})

add_subdirectory(tests)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)           #设置库文件的输出目录
add_library(${PROJECT_NAME}_lib SHARED ${EASY_COMPILER_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
