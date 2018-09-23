/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_norme_algo_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:45:34 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:45:36 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					norme_for_sort_links_1(t_room **buff,
					t_room *obj, int *i, t_room *tmp)
{
	if (tmp->distance_from_start < obj->distance_from_start)
	{
		*buff = tmp;
		(*i)++;
		return (1);
	}
	return (0);
}

int					norme_for_sort_links_2(int *i,
					t_room **obj, t_room *tmp, t_room *buff)
{
	if (tmp->distance_from_start > (*obj)->distance_from_start
		&& buff == NULL && tmp->start_end != END)
	{
		*i = 0;
		(*obj)->distance_from_start++;
		return (1);
	}
	return (0);
}

t_room				*is_way(t_room **room)
{
	int				i;
	t_room			*tmp;
	t_room			*buff;

	i = 0;
	tmp = (*room);
	while (tmp->start_end != END)
		tmp = tmp->next;
	while (tmp->link[i].name != NULL)
	{
		buff = que_search(room, tmp->link[i].name);
		if (buff->status == 0)
			return (buff);
		i++;
	}
	return (NULL);
}

void				add_to_the_way(t_room **room, t_room *tmp, t_room **way)
{
	t_room			*temp;
	t_room			*buff;
	t_room			*prev;

	buff = que_search(room, tmp->name);
	if ((*way) == NULL)
	{
		(*way) = (t_room *)ft_memalloc(sizeof(t_room));
		(*way)->status = buff->status;
		(*way)->start_end = buff->start_end;
		(*way)->name = ft_strdup(buff->name);
	}
	else
	{
		temp = (*way);
		while (temp->next != NULL)
			temp = temp->next;
		prev = temp;
		temp->next = (t_room *)ft_memalloc(sizeof(t_room));
		temp = temp->next;
		temp->prev = prev;
		temp->status = buff->status;
		temp->start_end = buff->start_end;
		temp->name = ft_strdup(buff->name);
	}
}

void				processing_of_the_ways(t_room **room, t_result **result)
{
	t_room			*way;
	t_room			*tmp;
	int				len;

	way = NULL;
	len = 0;
	search_the_way(room, &way);
	tmp = way;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	making_final_results(way, result, len);
}
