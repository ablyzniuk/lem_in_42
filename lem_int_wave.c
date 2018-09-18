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

void start_(t_room **room)
{
	t_room *tmp;
	t_room *que;
	t_room *for_que;

	tmp = (*room);
	que = NULL;
	semi_condition(*room);
	while (tmp->start_end != START)
		tmp = tmp->next;
	making_the_que(tmp,&que,NULL, 0);
	walking_on_links(&tmp,&que,room);
	tmp = (*room);
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
	indexing_main_list_by_distance(room,&que);
	free_que(&que);
}

void semi_condition(t_room *room)
{
	t_room *tmp;
	int s;

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

void walking_on_links(t_room **tmp, t_room **que, t_room **room)
{
	int i;
	t_room *buff;

	i = 0;
	if (!(*tmp)->link)
		return ;
	while ((*tmp)->link[i].name != NULL)
	{
		buff = que_search(room, (*tmp)->link[i].name);
		if (buff->status == 0)
		{
			making_the_que(buff, que, *tmp, (que_search(que,(*tmp)->name)->distance_from_start) + 1);
			buff->status = 1;
		}
		i++;
	}
	(*tmp)->status = 1;
}

void indexing_main_list_by_distance(t_room **room, t_room **que)
{
	t_room *tmp_room;
	t_room *tmp_que;

	tmp_que = (*que);
	while (tmp_que)
	{
		tmp_room = (*room);
		while (ft_strcmp(tmp_room->name,tmp_que->name) != 0)
			tmp_room = tmp_room->next;
		tmp_room->distance_from_start = tmp_que->distance_from_start;
		tmp_room->status = 0;
		tmp_room->parent_link = tmp_que->parent_link;
		tmp_que = tmp_que->next;
	}
}

void error_no_conditons_for_algo(t_room *que)
{
	int start;
	int end;

	start = 0;
	end = 0;
	while (que)
	{
		if (que->start_end == START)
			start++;
		if(que->start_end == END)
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

void error_no_conditons_for_algo_2(int start, int end)
{
	if (!start && !end)
	{
		ft_putstr("Critical error, insufficiency of data. Program terminated.\n");
		exit(0);
	}
}

void free_que(t_room **que)
{
	t_room *tmp;

	while ((*que))
	{
		tmp = (*que);
		(*que) = (*que)->next;
		ft_strdel(&tmp->name);
		ft_memdel((void *)&tmp);
	}
	ft_memdel((void **)que);
}

t_room *que_search(t_room **room, char *name)
{
	t_room *tmp;

	tmp = (*room);
	while (ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	return (tmp);
}

void making_the_que(t_room *room, t_room **que, t_room *parent_link, int len)
{
	t_room *tmp;

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

void making_final_results(t_room *start, t_result **result, int len)
{
	t_result *tmp;
	t_result *prev;

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
