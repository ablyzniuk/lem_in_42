/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_norme_algo_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:45:22 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:45:23 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				output_key_2_bonus(t_result **result)
{
	t_result		*tmp;
	int				i;

	i = 1;
	tmp = (*result);
	ft_putstr("\t Ant DISTRIBUTION on ways. \n\n");
	while (tmp)
	{
		ft_putstr("The ");
		ft_putnbr(i);
		ft_putstr(" way: len - ");
		ft_putnbr(tmp->len_of_the_way);
		ft_putstr(" | it will be sent on it - ");
		ft_putnbr(tmp->quant_of_ant);
		ft_putstr(" ants.\n");
		i++;
		tmp = tmp->next;
	}
	ft_putchar('\n');
}

t_result			*key_2_bonus_find_min(t_result **result)
{
	t_result		*tmp;
	t_result		*buff;

	tmp = (*result);
	buff = tmp;
	while (tmp)
	{
		if (tmp->quant_of_ant < buff->quant_of_ant
			&& tmp->len_of_the_way <= buff->len_of_the_way)
			buff = tmp;
		tmp = tmp->next;
	}
	return (buff);
}

void				key_bonus(t_result **resulted_ways)
{
	t_result		*tmp;
	t_room			*tmp_r;
	int				i;

	i = 1;
	tmp = *resulted_ways;
	ft_putstr("\t     WAYS FOR OUTPUT\n\n");
	while (tmp)
	{
		tmp_r = tmp->link_arr;
		if (key_bonus_check_for(resulted_ways))
			break ;
		key_bonus_for_norme(i, tmp);
		while (tmp_r)
		{
			bonus(tmp_r);
			tmp_r = tmp_r->next;
		}
		ft_putchar('\n');
		i++;
		tmp = tmp->next;
	}
	ft_putchar('\n');
}

int					key_bonus_check_for(t_result **result)
{
	t_result		*tmp;
	t_room			*tmp_r;

	if ((tmp = check_shortest(result)))
	{
		tmp_r = tmp->link_arr;
		key_bonus_for_norme(1, tmp);
		while (tmp_r)
		{
			bonus(tmp_r);
			tmp_r = tmp_r->next;
		}
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

void				key_bonus_for_norme(int i, t_result *tmp)
{
	ft_putstr("Way number: ");
	ft_putnbr(i);
	ft_putstr(" | Length: ");
	ft_putnbr(tmp->len_of_the_way);
	ft_putstr(" | ");
}
