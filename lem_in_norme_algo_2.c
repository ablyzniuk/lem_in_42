/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_norme_algo_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:45:07 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:45:08 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				norm_for_disribution_1(t_result
					**resulted_ways, t_result **tmp, int *min_len)
{
	*min_len = (*resulted_ways)->len_of_the_way;
	*tmp = (*resulted_ways);
	zero_status(resulted_ways);
	reverse_list(resulted_ways);
}

void				norm_for_disribution_2(t_result **resulted_ways,
					t_room **room)
{
	free_ways(resulted_ways);
	free_room(room);
}

void				free_ways(t_result **result)
{
	t_result		*buff;

	while (*result)
	{
		buff = (*result);
		free_room(&buff->link_arr);
		(*result) = (*result)->next;
		ft_memdel((void *)&buff);
	}
	ft_memdel((void **)result);
}

void				free_room(t_room **room)
{
	t_room			*buff;

	while (*room)
	{
		buff = (*room);
		(*room) = (*room)->next;
		ft_strdel(&buff->name);
		ft_memdel((void *)&buff->link);
		ft_memdel((void *)&buff);
	}
	ft_memdel((void **)room);
}

void				bzero_output(t_result **result)
{
	t_result		*tmp;
	t_room			*tmp_r;

	tmp = (*result);
	while (tmp)
	{
		tmp_r = tmp->link_arr;
		while (tmp_r)
		{
			tmp_r->output = 0;
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
}
