/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_norme_algo_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:44:59 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:45:00 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room				*rotate_to_end(t_room *room)
{
	while (room->next != NULL)
		room = room->next;
	return (room);
}

void				push_ants(t_room *room)
{
	t_room			*tmp_current;
	t_room			*tmp_next;

	tmp_current = room;
	if (room->next)
		tmp_next = room->next;
	else
		return ;
	tmp_next->what_ant = tmp_current->what_ant;
	tmp_next->status = 1;
	tmp_current->what_ant = 0;
	tmp_current->status = 0;
}

int					ants_distrib(t_room **room, int *ant)
{
	t_room			*tmp;

	tmp = (*room);
	if (tmp->start_end == START)
		tmp = tmp->next;
	if (tmp->status == 0 && tmp->what_ant == 0 && g_ants > 0)
	{
		tmp->status = 1;
		(*ant)++;
		g_ants--;
		tmp->output = 0;
		tmp->what_ant = *ant;
		return (1);
	}
	return (0);
}

void				que_for_output(t_room elem)
{
	ft_putchar('L');
	ft_putnbr(elem.what_ant);
	ft_putchar('-');
	ft_putstr(elem.name);
	ft_putchar(' ');
}

void				zero_status(t_result **resulted_ways)
{
	t_result		*tmp;
	t_room			*tmp_r;

	tmp = (*resulted_ways);
	while (tmp != NULL)
	{
		tmp_r = tmp->link_arr;
		while (tmp_r)
		{
			tmp_r->status = 0;
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
}
