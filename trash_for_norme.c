/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_for_norme.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:43:48 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/24 17:43:50 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			bonus_help(void)
{
	ft_putstr("\t\t\tLEM-IN\n\n");
	ft_putstr("Description: \n");
	ft_putstr("Its a simulation of the ant-farm.\n"
	"The rules are simple - ");
	ft_putstr("take the some number of ants and lead them to finish.\n");
	ft_putstr("'L' - number of ant and after '-' "
	"situated the number of room "
	"in which are the ant situated\n");
	ft_putstr("\n\nHere some addition tips: \n");
	ft_putstr(" '-w' arg - will show to you all "
	"possible ways which have found the programm.\n");
	ft_putstr("Also will show tou you length in "
	"rooms and their order by ants distribution. \n");
	ft_putstr("\n '-a' arg - will show to you "
	"distribution of ants on their ways.\n");
	ft_putstr("It will show to you how much"
	" of them will gain the finish room.\n\n");
}

int				s_e_choose(void)
{
	int			i;

	if (g_start_or_end == 1)
	{
		i = 1;
		g_start_or_end = 0;
	}
	else if (g_start_or_end == 2)
	{
		i = 2;
		g_start_or_end = 0;
	}
	else
	{
		i = 0;
		g_start_or_end = 0;
	}
	return (i);
}

int				is_symbol(char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void			ft_bzero_int(int *arr, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		arr[i] = 0;
		i++;
	}
}

void			norme_for_linker_allocation(t_room **link1,
											t_room **link2, int len)
{
	if ((*link1) && (*link1)->link == NULL)
		(*link1)->link = (t_room *)ft_memalloc(sizeof(t_room) * len);
	else if (!(*link1))
		error_no_links();
	if ((*link2) && (*link2)->link == NULL)
		(*link2)->link = (t_room *)ft_memalloc(sizeof(t_room) * len);
	else if (!(*link2))
		error_no_links();
}
