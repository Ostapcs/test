cmake_minimum_required(VERSION 3.9)
project(Set)

set(CMAKE_CXX_STANDARD 11)

add_executable(Set main.cpp)
add_subdirectory(lib/googletest-master/googletest)
include_directories(lib/googletest-master/googletest/include)
target_link_libraries(Set gtest)