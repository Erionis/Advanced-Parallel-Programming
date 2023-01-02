cmake_minimum_required(VERSION 3.24)

project(4_exercizes)
# genero la libreria dinamica
add_library(rational SHARED rational.cpp)
# compilo e collego l'esercizio alla libreria
add_executable(esercizio1 esercizio1.cpp)
target_link_libraries(esercizio1 rational)

add_executable(esercizio2 esercizio2.cpp)

add_executable(esercizio5 esercizio5.cpp)