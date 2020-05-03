cmake_minimum_required(VERSION 3.10)
project(docana CXX)
add_definitions("-O2 -g -Wall")
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(sample)

