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
# define LEM_IN_H

# include "libft/libft.h"
# define START 1
# define END   2

int					g_start_or_end;
int					g_ants;
int					g_fd;
int					g_h;
int					g_w;
int					g_a;

typedef struct		s_line
{
	char			*line;
	struct s_line	*next;
}					t_line;

typedef struct		s_room
{
	int				start_end;
	int				llr;
	int				list_len;
	int				coord_x;
	int				coord_y;
	int				distance_from_start;
	char			*name;
	int				status;
	int				what_ant;
	int				output;
	struct s_room	*parent_link;
	struct s_room	*link;
	struct s_room	*prev;
	struct s_room	*next;
}					t_room;

typedef struct		s_result
{
	struct s_room	*link_arr;
	int				len_of_the_way;
	int				quant_of_ant;
	struct s_result	*prev;
	struct s_result *next;
}					t_result;

int					is_it_way(t_room **way);
int					its_room(const char *line);
int					its_link(const char *line);
void				error_room(void);
void				error_quant_links(void);
void				one_(t_room *start, t_result **tmp);
void				bonus_help(void);
void				search_bonus(int argc, char **argv);
int					is_symbol(char *line);
void				norme_for_linker_allocation(t_room **link1,
					t_room **link2, int len, int *i);
void				norme_for_linker(int j, int k,
					t_room **link1, t_room **link2);
void				norme_for_distribution(t_result
					**resulted_ways, t_line **list);
void				print_list(t_line **list);
void				add_to_line(char *line, t_line **list);
void				norm_for_l_a_3(t_room *room, t_result **result);
void				processing_of_the_ways(t_room **room, t_result **result);
void				swap_list_elem(t_room *room, int len);
void				reverse_list(t_result **result);
void				norm_for_distributin_0(int *n,
					t_result **tmp, t_result **resulted_ways, int min_len);
void				norm_for_disribution_2(t_result
					**resulted_ways, t_room **room);
void				norm_for_disribution_1(t_result **resulted_ways,
					t_result **tmp, int *min_len);
void				norm_for_output(t_room **tmp_r);
int					norme_for_sort_links_2(int *i,
					t_room **obj, t_room *tmp, t_room *buff);
int					norme_for_sort_links_1(t_room **buff,
					t_room *obj, int *i, t_room *tmp);
void				key_2_bonus_for_norm(int *i,
					t_result **tmp, t_result **resulted_ways);
void				output_key_2_bonus_1(t_result *result);
int					key_bonus_check_for(t_result **result);
void				key_bonus_for_norme(int i, t_result *tmp);
t_result			*check_shortest(t_result **result);
void				error_no_links(void);
void				output_key_2_bonus(t_result **result);
t_result			*key_2_bonus_find_min(t_result **result);
void				key_2_bonus(t_result **resulted_ways);
void				bonus(t_room *room);
void				key_bonus(t_result **resulted_ways);
void				semi_condition(t_room *room);
int					len_list(t_room **room);
void				delete_buff(char **buff, int len);
void				free_room(t_room **room);
void				free_ways(t_result **result);
void				bzero_output(t_result **result);
t_room				*rotate_to_end(t_room *room);
void				all_push(t_result **result);
int					not_outputed(t_result **result);
void				output(t_result **result);
int					is_ant(t_result *result);
void				push_ants(t_room *room);
int					ants_distrib(t_room **room, int *ant);
void				zero_status(t_result **resulted_ways);
void				que_for_output(t_room elem);
t_room				*is_way(t_room **room);
void				distribution(t_room **room, t_result **resulted_ways);
void				distribution_of_ants(t_room **room, t_line **list);
void				making_final_results(t_room *start,
					t_result **result, int len);
void				add_to_the_way(t_room **room, t_room *tmp, t_room **way);
void				error_no_conditons_for_algo_2(int start, int end);
void				error_no_conditons_for_algo(t_room *que);
t_room				*sort_links(t_room **room, t_room *obj);
void				search_the_way(t_room **room, t_room **way);
void				read_and_valid(t_room **room, t_line **list);
void				free_que(t_room **que);
void				indexing_main_list_by_distance(t_room **room, t_room **que);
t_room				*que_search(t_room **que, char *room);
void				start_(t_room **room);
void				walking_on_links(t_room **tmp, t_room **que, t_room **room);
void				making_the_que(t_room *room,
					t_room **que, t_room *parent_link, int len);
void				room_coords_validator(t_room **room, char **buff);
void				checker_links(char **buff);
void				linker(t_room **room, char **line);
int					count_quant_coords(char **buff);
int					s_e_choose(void);
int					room_validator(char **buff);
void				working_with_room(char **buff, t_room **room, int s_e);
int					start_end(char **line);
int					checker_room(char **line, t_room **room);
int					ants(char **line);
void				create_links(t_room *link1,
					t_room *link2, char **buff, t_room **room);

#endif
