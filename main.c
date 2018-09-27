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
	t_line		*list;

	room = NULL;
	if (read(0, 0, 0) < 0)
	{
		ft_putstr("Invalid input data. Program terminated.\n");
		exit(0);
	}
	g_h = 0;
	g_fd = 0;
	g_w = 0;
	g_a = 0;
	search_bonus(argc, argv);
	read_and_valid(&room, &list);
	distribution_of_ants(&room, &list);
	return (0);
}

void			search_bonus(int argc, char **argv)
{
	int			i;

	i = 0;
	while (i < argc)
	{
		if (ft_strstr("-w", argv[i]))
			g_w = 1;
		if (ft_strstr("-a", argv[i]))
			g_a = 1;
		if (ft_strstr("-h", argv[i]))
			g_h = 1;
		i++;
	}
}

void			read_and_valid(t_room **room, t_line **list)
{
	char		*line;

	line = NULL;
	while (g_ants == 0)
	{
		if (!get_next_line(g_fd, &line))
		{
			ft_putstr("Error, invalid input data.\n");
			exit(0);
		}
		add_to_line(line, list);
		if (start_end(&line))
			continue ;
		ants(&line);
	}
	while (get_next_line(g_fd, &line) > 0)
	{
		add_to_line(line, list);
		if (start_end(&line))
			continue ;
		if (checker_room(&line, room) == 0)
			break ;
	}
	ft_strdel(&line);
	start_(room);
}

int				ants(char **line)
{
	int			i;

	i = 0;
	if (ft_atoi(*line) <= 0 || !is_symbol(*line))
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
	if (ft_strequ(*line, "##start"))
	{
		g_start_or_end = 1;
		ft_strdel(line);
		return (1);
	}
	else if (ft_strequ(*line, "##end"))
	{
		g_start_or_end = 2;
		ft_strdel(line);
		return (1);
	}
	else if (ft_strstr(*line, "#"))
	{
		ft_strdel(line);
		return (1);
	}
	return (0);
}
