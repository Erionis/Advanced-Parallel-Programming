cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(03_custom_types)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Scegli il tipo di build tra \"Debug\", \"Release\"
\"RelWithDebInfo\" o \"MinSizeRel\"."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic -Werror)

file(GLOB APP_SOURCES *.cpp)

foreach (sourcefile ${APP_SOURCES})
  get_filename_component(execname ${sourcefile} NAME_WLE)
  add_executable(${execname} "${execname}.cpp")
endforeach (sourcefile ${APP_SOURCES})
