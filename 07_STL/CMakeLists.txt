cmake_minimum_required(VERSION 3.24)

project(07_STL)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_compile_options(-Wall -Wextra -pedantic -Werror)

file(GLOB APP_SOURCES *.cpp)

foreach (sourcefile ${APP_SOURCES})
  get_filename_component(execname ${sourcefile} NAME_WLE)
  add_executable(${execname} "${execname}.cpp")
endforeach (sourcefile ${APP_SOURCES})

