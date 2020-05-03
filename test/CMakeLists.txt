cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(unit_test
    cosine_similarity_calculator_test.cc
    vector_utility_test.cc
)
target_link_libraries(unit_test docana GTest::GTest GTest::Main)
include_directories(${PROJECT_SOURCE_DIR}/include ${GTEST_INCLUDE_DIRS})

gtest_add_tests(TARGET unit_test)

