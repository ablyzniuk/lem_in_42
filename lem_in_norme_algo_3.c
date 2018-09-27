/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_norme_algo_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:45:17 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:45:19 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				bonus(t_room *room)
{
	ft_putstr(room->name);
	if (room->next)
		ft_putstr("<-");
}

void				reverse_list(t_result **result)
{
	t_result		*tmp;
	t_room			*start;
	int				i;

	i = 1;
	tmp = (*result);
	while (tmp)
	{
		tmp->quant_of_ant = 0;
		error_no_conditons_for_algo(tmp->link_arr);
		swap_list_elem(tmp->link_arr, tmp->len_of_the_way);
		tmp = tmp->next;
	}
	if ((tmp = check_shortest(result)))
	{
		start = tmp->link_arr;
		tmp->link_arr = tmp->link_arr->next;
		while (g_ants >= i)
		{
			tmp->link_arr->what_ant++;
			que_for_output(*tmp->link_arr);
			i++;
		}
		one_(start, &tmp);
	}
}

t_result			*check_shortest(t_result **result)
{
	t_result		*tmp;

	tmp = (*result);
	while (tmp)
	{
		if (tmp->len_of_the_way == 2)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

inline void			distribution(t_room **room, t_result **resulted_ways)
{
	int				min_len;
	t_result		*tmp;
	int				n;

	n = 0;
	norm_for_disribution_1(resulted_ways, &tmp, &min_len);
	while (is_ant(*resulted_ways))
	{
		norm_for_distributin_0(&n, &tmp, resulted_ways, min_len);
		while (not_outputed(resulted_ways))
			output(resulted_ways);
		bzero_output(resulted_ways);
		all_push(resulted_ways);
		if (!tmp)
		{
			tmp = (*resulted_ways);
			ft_putchar('\n');
			continue ;
		}
	}
	norm_for_disribution_2(resulted_ways, room);
}

void				norm_for_distributin_0(int *n,
					t_result **tmp, t_result **resulted_ways, int min_len)
{
	while (*tmp)
	{
		if (g_ants - min_len >= (*tmp)->len_of_the_way - min_len && g_ants)
		{
			if (ants_distrib(&(*tmp)->link_arr, n))
				(*tmp)->quant_of_ant++;
		}
		else if (g_ants - min_len < (*tmp)->len_of_the_way - min_len && g_ants)
		{
			if (ants_distrib(&
	(key_2_bonus_find_min(resulted_ways))->link_arr, n))
				(key_2_bonus_find_min(resulted_ways))->quant_of_ant++;
		}
		(*tmp) = (*tmp)->next;
	}
}
