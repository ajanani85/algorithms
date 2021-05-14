cmake_minimum_required (VERSION 2.6)

project (path_planning)

include_directories(include)

add_executable(path_planning src/path_planning.cpp 
							 src/path_planning_DFS.cpp
							 src/path_planning_base.cpp)
