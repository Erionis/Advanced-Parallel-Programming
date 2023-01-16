cmake_minimum_required(VERSION 3.24)

project(08_exceptions)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(01_try_catch 01_try_catch.cpp)
add_executable(02_propagation 02_propagation.cpp)
add_executable(03_throw_noexcept 03_throw_noexcept.cpp)
add_executable(04_custom_exception 04_custom_exception.cpp)

