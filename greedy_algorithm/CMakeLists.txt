cmake_minimum_required (VERSION 2.6)

project (greedy_algorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(non_overlapping_intervals src/non_overlapping_intervals.cpp)
add_executable(maximum_overlapping_intervals src/maximum_overlapping_intervals.cpp)
add_executable(minimum_jumps src/minimum_jumps.cpp)