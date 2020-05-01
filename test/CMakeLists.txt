cmake_minimum_required(VERSION 3.10)

include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)
download_project(PROJ googletest
                 GIT_REPOSITORY https://github.com/google/googletest.git
                 GIT_TAG master
                 UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

add_executable(unit_test test.cc)
target_link_libraries(unit_test docana gtest_main)
include_directories(${PROJECT_SOURCE_DIR}/src)

target_compile_features(unit_test PUBLIC cxx_std_11)

include(GoogleTest)
gtest_add_tests(TARGET unit_test)

