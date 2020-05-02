cmake_minimum_required(VERSION 3.10)
project(docana CXX)
set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Wall")
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(sample)

