/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_norme_wave_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:43:50 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:43:53 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			error_no_conditons_for_algo_2(int start, int end)
{
	if (!start && !end)
	{
		ft_putstr("Critical error,"
	"insufficiency of data. Program terminated.\n");
		exit(0);
	}
}

inline void		free_que(t_room **que)
{
	t_room		*tmp;

	while ((*que))
	{
		tmp = (*que);
		(*que) = (*que)->next;
		ft_strdel(&tmp->name);
		ft_memdel((void *)&tmp);
	}
	ft_memdel((void **)que);
}

t_room			*que_search(t_room **room, char *name)
{
	t_room		*tmp;

	tmp = (*room);
	while (ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	return (tmp);
}

inline void		making_the_que(t_room *room,
				t_room **que, t_room *parent_link, int len)
{
	t_room		*tmp;

	if ((*que) == NULL)
	{
		(*que) = (t_room *)ft_memalloc(sizeof(t_room));
		(*que)->name = ft_strdup(room->name);
		(*que)->start_end = room->start_end;
		(*que)->parent_link = parent_link;
		(*que)->distance_from_start = len;
		(*que)->next = NULL;
	}
	else
	{
		tmp = (*que);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_room *)ft_memalloc(sizeof(t_room));
		tmp = tmp->next;
		tmp->parent_link = parent_link;
		tmp->distance_from_start = len;
		tmp->name = ft_strdup(room->name);
		tmp->start_end = room->start_end;
	}
}

inline void		making_final_results(t_room *start, t_result **result, int len)
{
	t_result	*tmp;
	t_result	*prev;

	if ((*result) == NULL)
	{
		(*result) = (t_result *)ft_memalloc(sizeof(t_result));
		(*result)->link_arr = start;
		(*result)->len_of_the_way = len;
	}
	else
	{
		tmp = (*result);
		while (tmp->next != NULL)
			tmp = tmp->next;
		prev = tmp;
		tmp->next = (t_result *)ft_memalloc(sizeof(t_result));
		tmp = tmp->next;
		tmp->prev = prev;
		tmp->link_arr = start;
		tmp->len_of_the_way = len;
	}
}
