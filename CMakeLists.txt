cmake_minimum_required(VERSION 3.9)
project(Lem_in C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(libft LIBFT_SRC)
add_library(ft STATIC ${LIBFT_SRC})

add_executable(Lem_in main.c lem-in_linker.c lem_in_algo.c lem_int_wave.c)
target_link_libraries(Lem_in ft)