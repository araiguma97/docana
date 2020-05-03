cmake_minimum_required(VERSION 3.10)

include_directories(/usr/local/include ${PROJECT_SOURCE_DIR}/include/docana)
add_executable(sample sample.cc)
target_link_libraries(sample docana)

