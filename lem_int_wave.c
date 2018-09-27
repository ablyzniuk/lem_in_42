/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_int_wave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 20:01:57 by ablizniu          #+#    #+#             */
/*   Updated: 2018/08/23 20:01:58 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline void		start_(t_room **room)
{
	t_room		*tmp;
	t_room		*que;
	t_room		*for_que;

	tmp = (*room);
	que = NULL;
	semi_condition(*room);
	while (tmp->start_end != START)
		tmp = tmp->next;
	making_the_que(tmp, &que, NULL, 0);
	walking_on_links(&tmp, &que, room);
	for_que = que;
	tmp->status = 1;
	for_que = for_que->next;
	while (for_que)
	{
		tmp = que_search(room, for_que->name);
		walking_on_links(&tmp, &que, room);
		for_que = for_que->next;
	}
	error_no_conditons_for_algo(que);
	indexing_main_list_by_distance(room, &que);
	free_que(&que);
}

void			semi_condition(t_room *room)
{
	t_room		*tmp;
	int			s;

	s = 0;
	tmp = room;
	while (tmp)
	{
		if (tmp->start_end == 1)
			s++;
		tmp = tmp->next;
	}
	if (s == 0 || s > 1)
	{
		ft_putstr("Error, no ##START conditions. Program terminated\n");
		exit(0);
	}
}

inline void		walking_on_links(t_room **tmp, t_room **que, t_room **room)
{
	int			i;
	t_room		*buff;

	i = 0;
	if (!(*tmp)->link)
		return ;
	while ((*tmp)->link[i].name && i < que_search(room, (*tmp)->name)->llr)
	{
		buff = que_search(room, (*tmp)->link[i].name);
		if (buff->status == 0)
		{
			making_the_que(buff, que,
			*tmp, (que_search(que, (*tmp)->name)->distance_from_start) + 1);
			buff->status = 1;
		}
		i++;
	}
	(*tmp)->status = 1;
}

void			indexing_main_list_by_distance(t_room **room, t_room **que)
{
	t_room		*tmp_room;
	t_room		*tmp_que;

	tmp_que = (*que);
	while (tmp_que)
	{
		tmp_room = (*room);
		while (ft_strcmp(tmp_room->name, tmp_que->name) != 0)
			tmp_room = tmp_room->next;
		tmp_room->distance_from_start = tmp_que->distance_from_start;
		tmp_room->status = 0;
		tmp_room->parent_link = tmp_que->parent_link;
		tmp_que = tmp_que->next;
	}
}

void			error_no_conditons_for_algo(t_room *que)
{
	int			start;
	int			end;

	start = 0;
	end = 0;
	while (que)
	{
		if (que->start_end == START)
			start++;
		if (que->start_end == END)
			end++;
		que = que->next;
	}
	if ((start == 0 || start > 1) && end)
	{
		ft_putstr("Error, no ##START conditions. Program terminated\n");
		exit(0);
	}
	else if ((end == 0 || end > 1) && start)
	{
		ft_putstr("Error, no ##END conditions. Program terminated\n");
		exit(0);
	}
	error_no_conditons_for_algo_2(start, end);
}
