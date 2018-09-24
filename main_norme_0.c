/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norme_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:39:24 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:39:25 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			room_coords_validator(t_room **room, char **buff)
{
	t_room		*tmp;

	tmp = (*room);
	while (tmp != NULL)
	{
		if (tmp->coord_x == ft_atoi(buff[1])
			&& tmp->coord_y == ft_atoi(buff[2]))
		{
			ft_putstr("Error, invalid room coordinates, program terminated.\n");
			exit(0);
		}
		tmp = tmp->next;
	}
}

void			norm_for_l_a_3(t_room *room, t_result **result)
{
	(*result)->link_arr = room;
	g_ants = 0;
}

void			add_to_line(char *line, t_line **list)
{
	t_line		*tmp;

	if (*list == NULL)
	{
		(*list) = (t_line *)ft_memalloc(sizeof(t_line));
		(*list)->line = ft_strdup(line);
	}
	else
	{
		tmp = (*list);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_line *)ft_memalloc(sizeof(t_line));
		tmp = tmp->next;
		tmp->line = ft_strdup(line);
		tmp->next = NULL;
	}
}

void			print_list(t_line **list)
{
	t_line		*tmp;
	t_line		*start;

	start = (*list);
	while (start)
	{
		tmp = start;
		ft_putstr(tmp->line);
		ft_putchar('\n');
		start = start->next;
		ft_strdel(&tmp->line);
		ft_memdel((void *)&tmp);
	}
	ft_putchar('\n');
}

void			norme_for_distribution(t_result **resulted_ways, t_line **list)
{
	t_result	*res;

	print_list(list);
	if (g_h)
		bonus_help();
	if (g_w)
		key_bonus(resulted_ways);
	if (g_a)
	{
		if ((res = check_shortest(resulted_ways)))
			output_key_2_bonus_1(res);
		else
			key_2_bonus(resulted_ways);
	}
}
