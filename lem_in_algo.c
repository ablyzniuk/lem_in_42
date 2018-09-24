/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 16:50:40 by ablizniu          #+#    #+#             */
/*   Updated: 2018/08/21 16:50:42 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				search_the_way(t_room **room, t_room **way)
{
	t_room			*tmp;

	tmp = (*room);
	while (tmp->start_end != END)
		tmp = tmp->next;
	while (tmp->start_end != START)
	{
		add_to_the_way(room, tmp, way);
		tmp = sort_links(room, tmp);
		if (tmp == NULL)
		{
			tmp = is_way(room);
			if (tmp == NULL)
				break ;
		}
		if (tmp->start_end != START)
			tmp->status = 1;
	}
	if (tmp != NULL)
		add_to_the_way(room, tmp, way);
}

t_room				*sort_links(t_room **room, t_room *obj)
{
	t_room			*buff;
	t_room			*tmp;
	int				safe;
	int				i;

	i = 0;
	buff = NULL;
	safe = obj->distance_from_start;
	while (obj->link[i].name != NULL && i < obj->llr)
	{
		tmp = que_search(room, obj->link[i].name);
		if (tmp->status == 0)
		{
			if (norme_for_sort_links_1(&buff, obj, &i, tmp))
				continue ;
			else if (norme_for_sort_links_2(&i, &obj, tmp, buff))
				continue ;
		}
		i++;
	}
	obj->distance_from_start = safe;
	return (buff);
}
