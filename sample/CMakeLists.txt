cmake_minimum_required(VERSION 3.10)

add_executable(sample sample.cc)
target_link_libraries(sample docana)
include_directories(${PROJECT_SOURCE_DIR}/src)

