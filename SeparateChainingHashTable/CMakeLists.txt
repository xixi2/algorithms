cmake_minimum_required(VERSION 3.14)
project(SeparateChainingHashTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(SeparateChainingHashTable main.cpp SeparateChaining.h SeparateChaining.cpp)