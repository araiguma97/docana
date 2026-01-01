cmake_minimum_required(VERSION 3.10)
project(docana CXX)

set(CMAKE_CXX_STANDARD 14)
add_definitions("-O2 -g -Wall")

find_path(MECAB_INCLUDE_DIR mecab.h
    HINTS /opt/homebrew/include /usr/local/include
)
find_library(MECAB_LIBRARY NAMES mecab
    HINTS /opt/homebrew/lib /usr/local/lib
)

if(NOT MECAB_INCLUDE_DIR OR NOT MECAB_LIBRARY)
    message(FATAL_ERROR "MeCab not found. Please install it: brew install mecab")
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
