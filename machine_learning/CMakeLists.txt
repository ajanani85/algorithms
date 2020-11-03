cmake_minimum_required (VERSION 2.6)

project (machine_learning)

find_package(OpenCV REQUIRED)

add_executable(machine_learning machine_learning.cpp)
target_link_libraries(machine_learning ${OpenCV_LIBRARIES})