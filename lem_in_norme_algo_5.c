/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_norme_algo_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:45:27 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:45:28 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				swap_list_elem(t_room *room, int len)
{
	t_room			*tmp_1;
	t_room			*tmp_2;
	char			*buff;
	int				start_end;

	tmp_1 = room;
	while (tmp_1->next != NULL)
		tmp_1 = tmp_1->next;
	tmp_2 = tmp_1;
	tmp_1 = room;
	len -= 2;
	while (len != 0)
	{
		buff = tmp_1->name;
		start_end = tmp_1->start_end;
		tmp_1->name = tmp_2->name;
		tmp_1->start_end = tmp_2->start_end;
		tmp_2->name = buff;
		tmp_2->start_end = start_end;
		tmp_1 = tmp_1->next;
		tmp_2 = tmp_2->prev;
		len--;
	}
}

void				distribution_of_ants(t_room **room)
{
	t_room			*tmp;
	t_result		*res;
	t_result		*resulted_ways;
	int				i;

	i = 0;
	tmp = (*room);
	resulted_ways = NULL;
	while (tmp && tmp->start_end != END)
		tmp = tmp->next;
	while (tmp && tmp->link[i].name != NULL)
	{
		processing_of_the_ways(room, &resulted_ways);
		i++;
	}
	if (g_w)
		key_bonus(&resulted_ways);
	if (g_a)
	{
		if ((res = check_shortest(&resulted_ways)))
			output_key_2_bonus_1(res);
		else
			key_2_bonus(&resulted_ways);
	}
	distribution(room, &resulted_ways);
}

void				key_2_bonus(t_result **resulted_ways)
{
	int				i;
	t_result		*tmp;

	i = g_ants;
	tmp = (*resulted_ways);
	while (i)
	{
		while (tmp)
		{
			key_2_bonus_for_norm(&i, &tmp, resulted_ways);
			tmp = tmp->next;
		}
		tmp = (*resulted_ways);
	}
	output_key_2_bonus(resulted_ways);
}

void				key_2_bonus_for_norm(int *i,
					t_result **tmp, t_result **resulted_ways)
{
	if (*i - (*resulted_ways)->len_of_the_way >=
		(*tmp)->len_of_the_way - (*resulted_ways)->len_of_the_way && *i)
	{
		(*tmp)->quant_of_ant++;
		(*i)--;
	}
	else if (*i - (*resulted_ways)->len_of_the_way <
	(*tmp)->len_of_the_way - (*resulted_ways)->len_of_the_way && *i)
	{
		((*tmp) = key_2_bonus_find_min(resulted_ways))->quant_of_ant++;
		(*i)--;
	}
}

void				output_key_2_bonus_1(t_result *result)
{
	t_result		*tmp;

	tmp = result;
	ft_putstr("The ");
	ft_putnbr(1);
	ft_putstr(" way: len - ");
	ft_putnbr(tmp->len_of_the_way);
	ft_putstr(" | it will be sent on it - ");
	ft_putnbr(g_ants);
	ft_putstr(" ants.\n");
	ft_putchar('\n');
}
