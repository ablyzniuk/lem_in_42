/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <ablizniu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:45:54 by ablizniu          #+#    #+#             */
/*   Updated: 2018/08/10 21:26:07 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				main(int argc, char **argv)
{
	t_room		*room;
	int			i;

	i = 0;
	room = NULL;
	if (read(0, 0, 0) < 0)
	{
		ft_putstr("Invalid input data. Program terminated.\n");
		exit(0);
	}
	g_fd = 0;
	g_w = 0;
	g_a = 0;
	while (i < argc)
	{
		if (ft_strstr("-w", argv[i]))
			g_w = 1;
		if (ft_strstr("-a", argv[i]))
			g_a = 1;
		i++;
	}
	read_and_valid(&room);
	distribution_of_ants(&room);
	return (0);
}

void			read_and_valid(t_room **room)
{
	char		*line;

	line = NULL;
	if (get_next_line(g_fd, &line) > 0 && g_ants == 0)
	{
		ft_putstr(line);
		ft_putchar('\n');
		ants(&line);
	}
	while (get_next_line(g_fd, &line) > 0)
	{
		ft_putstr(line);
		ft_putchar('\n');
		checker_room(&line, room);
	}
	ft_strdel(&line);
	ft_putchar('\n');
	start_(room);
}

int				ants(char **line)
{
	int			i;

	i = 0;
	if (**line == '-' || !ft_isdigit((int)(*line)[i]))
	{
		ft_putstr("Error, invalid ants condition.\n");
		ft_strdel(line);
		exit(0);
	}
	else if (ft_isdigit((int)(*line)[i]))
	{
		g_ants = (unsigned int)ft_atoi(*line);
		ft_strdel(line);
		return (1);
	}
	return (0);
}

int				start_end(char **line)
{
	if (ft_strstr(*line, "##start"))
	{
		g_start_or_end = 1;
		free(*line);
		return (1);
	}
	else if (ft_strstr(*line, "##end"))
	{
		g_start_or_end = 2;
		free(*line);
		return (1);
	}
	else if (ft_strstr(*line, "#"))
	{
		g_start_or_end = 0;
		free(*line);
		return (1);
	}
	return (0);
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
