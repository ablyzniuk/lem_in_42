/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_norme_algo_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:45:03 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:45:04 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					is_ant(t_result *result)
{
	t_result		*tmp;
	t_room			*tmp_r;

	tmp = result;
	while (tmp)
	{
		tmp_r = tmp->link_arr;
		while (tmp_r)
		{
			if ((tmp_r->what_ant != 0 && tmp_r->status != 0) || g_ants > 0)
				return (1);
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void				output(t_result **result)
{
	t_result		*tmp;
	t_room			*tmp_r;

	tmp = *result;
	while (tmp)
	{
		tmp_r = rotate_to_end(tmp->link_arr);
		while (tmp_r)
		{
			if (tmp_r->status && tmp_r->what_ant && !tmp_r->output)
			{
				que_for_output(*tmp_r);
				tmp_r->output = 1;
				if (tmp_r->start_end == END)
					norm_for_output(&tmp_r);
				break ;
			}
			tmp_r = tmp_r->prev;
		}
		tmp = tmp->next;
	}
}

void				norm_for_output(t_room **tmp_r)
{
	(*tmp_r)->what_ant = 0;
	(*tmp_r)->what_ant = 0;
	(*tmp_r)->status = 0;
	(*tmp_r)->output = 1;
}

void				all_push(t_result **result)
{
	t_result		*tmp;
	t_room			*r;

	tmp = (*result);
	while (tmp)
	{
		r = rotate_to_end(tmp->link_arr);
		while (r)
		{
			if (r->start_end != END && r->what_ant && r->status)
			{
				r->output = 0;
				push_ants(r);
			}
			r = r->prev;
		}
		tmp = tmp->next;
	}
}

int					not_outputed(t_result **result)
{
	t_result		*tmp;
	t_room			*room;

	tmp = (*result);
	while (tmp)
	{
		room = tmp->link_arr;
		while (room)
		{
			if (room->what_ant != 0 && room->output == 0)
				return (1);
			room = room->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
