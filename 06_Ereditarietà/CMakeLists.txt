cmake_minimum_required(VERSION 3.24)

project(06_inheritance)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(01_inheritance_type 01_inheritance_type.cpp)

add_executable(02_dynamic_cast 02_dynamic_cast.cpp)

add_executable(03_multiple_inheritance 03_multiple_inheritance.cpp)

add_executable(04_overriding_and_virtual 04_overriding_and_virtual.cpp)

add_executable(05_pure_virtual 05_pure_virtual.cpp)

add_executable(06_virtual_destroyer 06_virtual_destroyer.cpp)

add_executable(07_final_methods 07_final_methods.cpp)