cmake_minimum_required (VERSION 2.6)

project (sudoku_solver)

find_package(OpenCV REQUIRED)

add_executable(sudoku_solver sudoku_solver.cpp)
target_link_libraries(sudoku_solver ${OpenCV_LIBRARIES})