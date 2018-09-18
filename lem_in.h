/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <ablizniu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 17:51:17 by ablizniu          #+#    #+#             */
/*   Updated: 2018/08/10 21:25:24 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H

#include "libft/libft.h"
# define START 1
# define END   2

int					g_start_or_end;
unsigned int		g_ants;
int					g_fd;
int 				g_key;

typedef struct		s_room
{
	int				start_end;
	int				coord_x;
	int				coord_y;
	int				distance_from_start;
	char			*name;
	int				status;
	int 			what_ant;
	int 			output;
	struct s_room	*parent_link;
	struct s_room	*link;
	struct s_room	*prev;
	struct s_room	*next;
}					t_room;

typedef struct	s_result
{
	struct		s_room *link_arr;
	int			len_of_the_way;
	struct		s_result *prev;
	struct		s_result *next;
}				t_result;

void	semi_condition(t_room *room);
int		len_list(t_room **room);
void	delete_buff(char **buff, int len);
void	free_room(t_room **room);
void	free_ways(t_result **result);
void	bzero_output(t_result **result);
t_room	*rotate_to_end(t_room *room);
void	all_push(t_result **result);
int		not_outputed(t_result **result);
void	output(t_result **result);
int		is_ant(t_result *result);
void	push_ants(t_room *room);
int		ants_distrib(t_room **room, int *ant);
void	zero_status(t_result **resulted_ways);
void	que_for_output(t_room elem);
t_room	*is_way(t_room **room);
void	distribution(t_room **room, t_result **resulted_ways);
void 	distribution_of_ants(t_room **room);
void	making_final_results(t_room *start, t_result **result, int len);
void	add_to_the_way(t_room **room, t_room *tmp, t_room **way);
void	error_no_conditons_for_algo_2(int start, int end);
void	error_no_conditons_for_algo(t_room *que);
t_room	*sort_links(t_room **room, t_room *obj);
void	search_the_way(t_room **room, t_room **way);
void 	read_and_valid(t_room **room);
void	free_que(t_room **que);
void	indexing_main_list_by_distance(t_room **room, t_room **que);
t_room	*que_search(t_room **que, char *room);
void	start_(t_room **room);
void	walking_on_links(t_room **tmp,t_room **que, t_room **room);
void	making_the_que(t_room *room, t_room **que, t_room *parent_link, int len);
void	room_coords_validator(t_room **room, char **buff);
void	checker_links(t_room **room, char **buff);
void	linker(t_room **room, char **line);
void	count_quant_coords(char **buff);
int		s_e_choose(void);
void	room_validator(char **buff);
void	working_with_room(char **buff, t_room **room, int s_e);
int		start_end(t_room **room, char **line);
int		checker_room(char **line, t_room **room);
int		ants(char **line);
void	create_links(t_room *link1, t_room *link2, char **buff, t_room **room);

#endif
