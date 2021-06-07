cmake_minimum_required(VERSION 3.17)
project(easy_compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(easy_compiler main.cpp lexer.cpp log.cpp)