cmake_minimum_required (VERSION 2.6)

project (prefix_sum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(prefix_sum src/prefix_sum.cpp)