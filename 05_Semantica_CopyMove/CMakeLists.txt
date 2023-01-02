cmake_minimum_required(VERSION 3.24)

set (CMAKE_CXX_STANDARD 11) # per far funzionare Cmake!!

project(05_copy_move_semantics)   # nome del progetto

add_executable(esempio1 esempio1.cpp)


add_executable(esempio2_a esempio2.cpp) #senza MOVE
add_executable(esempio2_b esempio2.cpp) # con MOVE
target_compile_definitions(esempio2_b PUBLIC MOVE_ON)

# questo serve per aggiungere tra i target del nostro progetto
# la libreria dinamica (SHARED) rational
add_library(rational rational.cpp)
# aggiungere tra i target l'eseguibilie esempio3
add_executable(esempio3 esempio3.cpp)
# "esempio3" deve essere linkato alla libreria "rational"
target_link_libraries(esempio3 rational)

# cmake . -G Ninja