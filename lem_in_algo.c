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
#include <stdio.h>

void search_the_way(t_room **room, t_room **way)
{
	t_room *tmp;
	t_room *buff;

	tmp = (*room);
	while (tmp->start_end != END)
		tmp = tmp->next;
	while (tmp->start_end != START)
	{
		add_to_the_way(room,tmp,way);
		tmp = sort_links(room, tmp);
		if (tmp == NULL)
		{
			if ((tmp = is_way(room)) != NULL);
			else
				break;
		}
		if (tmp->start_end != START)
			tmp->status = 1;
	}
	if (tmp != NULL)
		add_to_the_way(room,tmp,way);
}

t_room *sort_links(t_room **room, t_room *obj)
{
	t_room *buff;
	t_room *tmp;
	int safe;
	int i;

	i = 0;
	buff = NULL;
	safe = obj->distance_from_start;
	while (obj->link[i].name != NULL)
	{
		tmp = que_search(room, obj->link[i].name);
		if (tmp->status == 0)
		{
			if ((tmp->distance_from_start < obj->distance_from_start))
			{
				buff = tmp;
				i++;
				continue ;
			}
			else if (tmp->distance_from_start > obj->distance_from_start && buff == NULL && tmp->start_end != END)
			{
				i = 0;
				obj->distance_from_start++;
				continue ;
			}
		}
		i++;
	}
	obj->distance_from_start = safe;
	return (buff);
}

t_room *is_way(t_room **room)
{
	int i;
	t_room *tmp;
	t_room *buff;

	i = 0;
	tmp = (*room);
	while (tmp->start_end != END)
		tmp = tmp->next;
	while (tmp->link[i].name != NULL)
	{
		buff = que_search(room,tmp->link[i].name);
		if (buff->status == 0)
			return (buff);
		i++;
	}
	return (NULL);
}

void add_to_the_way(t_room **room, t_room *tmp, t_room **way)
{
	t_room *temp;
	t_room *buff;

	buff = que_search(room,tmp->name);
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
		temp->next = (t_room *)ft_memalloc(sizeof(t_room));
		temp = temp->next;
		temp->status = buff->status;
		temp->start_end = buff->start_end;
		temp->name = ft_strdup(buff->name);
	}
}

void processing_of_the_ways(t_room **room, t_result **result)
{
	t_room *way;
	t_room *tmp;
	int len;

	way = NULL;
	len = 0;
	search_the_way(room, &way);
	tmp = way;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	making_final_results(way,result,len);

}

void  distribution_of_ants(t_room **room)
{
	t_room		*tmp;
	t_result	*resulted_ways;
	t_room		*buff;
	int i;

	i = 0;
	tmp = (*room);
	resulted_ways = NULL;
	while (tmp && tmp->start_end != END)
		tmp = tmp->next;
	while (tmp && tmp->link[i].name != NULL)
	{
		processing_of_the_ways(room,&resulted_ways);
		i++;
	}
	distribution(room,&resulted_ways);
}

/* ------------------------------------------------------------------------*/
//		15 ants, len rooms - 4. 6. 8.									   //
//		пускаем первого по мин пути тобишь на 4 -- количество уже 14	   //
//		14 - 4 >= (путь куда сейчас будем пускать) - 6 - (мин путь) 4	   //
//		(если уравнение сбывается то пускаем на 6) тобишь минус 1 муравей  //
//		13 - 4 >= 8 - 4	тут пускаем на 8								   //
// 		и так далее														   //
/*-------------------------------------------------------------------------*/


void distribution(t_room **room, t_result **resulted_ways)
{
	int min_len;
	t_result *tmp;
	//sort_for_distribution(resulted_ways);

	min_len = (*resulted_ways)->len_of_the_way;
	tmp = (*resulted_ways);
	while (tmp)
	{
		if (g_ants - min_len >= tmp->len_of_the_way - min_len)
		{

		}
	}
}

void output_final()
//int		compare(int a, int b)
//{
//	if (a <= b) //1 < 2 = 1
//		return (1);
//	else // 2 > 1 = 0
//		return (0);
//}
//
//int		tri(t_result *list, int (*cmp)(int, int))
//{
//	while (list->next != NULL)
//	{
//		if ((*cmp)(list->len_of_the_way,list->next->len_of_the_way) == 0)
//			return (0);
//		list = list->next;
//	}
//	return (1);
//}
//
//t_result 	*sort_list(t_result **list, int (*cmp)(int, int))
//{
//	t_result *first;
//	t_result *swap;
//
//	first = (*list);
//	while (tri(first, compare) == 0)
//	{
//		(*list) = first;
//		while ((*list)->next != NULL)
//		{
//			if ((*cmp)((*list)->len_of_the_way,(*list)->next->len_of_the_way) == 0)
//			{
//				swap = (*list);
//				(*list) = (*list)->next;
//				(*list)->next = swap;
//			}
//			(*list) = (*list)->next;
//		}
//	}
//	return (first);
//}
//
//void sort_for_distribution(t_result **resulted_ways)
//{
//	t_result **tmp;
//
//	tmp = resulted_ways;
//	(*resulted_ways) = sort_list(tmp,compare);
//}
