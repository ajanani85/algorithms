cmake_minimum_required (VERSION 2.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

project (path_planning)

include_directories(include)

add_executable(path_planning src/path_planning.cpp
							 src/path_planning_base.cpp
							 src/path_planning_BFS.cpp)
