cmake_minimum_required(VERSION 3.24)

project(somma_cl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCL REQUIRED)

INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS})

LINK_DIRECTORIES(${OpenCL_LIBRARY})

add_executable(array_sum_comparison array_sum_comparison.cpp)
target_link_libraries(array_sum_comparison ${OpenCL_LIBRARY})

add_executable(matrix_mult_comparison matrix_mult_comparison.cpp)
target_link_libraries(matrix_mult_comparison ${OpenCL_LIBRARY})

add_executable(opencl_info opencl_info.cpp)
target_link_libraries(opencl_info ${OpenCL_LIBRARY})

add_executable(array_sum array_sum.c)
target_link_libraries(array_sum ${OpenCL_LIBRARY})