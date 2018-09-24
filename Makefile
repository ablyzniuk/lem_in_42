# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/23 16:02:23 by ablizniu          #+#    #+#              #
#    Updated: 2018/09/23 16:02:26 by ablizniu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
PATH_LB = libft/
NAME_LB = $(PATH_LB)libft.a
FLAGS = -Wall -Wextra -Werror
CC = clang

OBJS = main.c lem_in_linker.c lem_in_algo.c lem_int_wave.c \
main_norme.c main_norme_0.c lem_in_norme_linker_0.c lem_in_norme_wave_0.c \
 lem_in_norme_algo_0.c lem_in_norme_algo_1.c lem_in_norme_algo_2.c lem_in_norme_algo_3.c \
 lem_in_norme_algo_4.c lem_in_norme_algo_5.c lem_in_norme_algo_6.c \
 trash_for_norm*
SRC_LB = libft/*.c
OBJ_LB = *.o

all: $(NAME)

$(NAME): $(NAME_LB) $(OBJ_PATH)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(NAME_LB)

$(NAME_LB):
	make -C libft

clean:
	@rm -f *.o
fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft 
re: fclean all