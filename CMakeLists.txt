cmake_minimum_required(VERSION 3.9)
project(Lem_in C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(libft LIBFT_SRC)
add_library(ft STATIC ${LIBFT_SRC})

add_executable(Lem_in main.c lem_in_linker.c lem_in_algo.c lem_int_wave.c main_norme.c main_norme_0.c lem_in_norme_linker_0.c lem_in_norme_wave_0.c lem_in_norme_algo_0.c lem_in_norme_algo_1.c lem_in_norme_algo_2.c lem_in_norme_algo_3.c lem_in_norme_algo_4.c lem_in_norme_algo_5.c lem_in_norme_algo_6.c trash_for_norme.c trash_for_norme_1.c trash_cor_norme_3.c)
target_link_libraries(Lem_in ft)