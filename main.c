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
#include <stdio.h>

int main(int argc, char **argv)
{
	t_room *room;

	room = NULL;
	fd = open(argv[1],O_RDONLY);
	read_and_valid(&room);
	distribution_of_ants(&room);
	//search_the_way(&room);
	return 0;
}

void read_and_valid(t_room **room)
{
	char *line;

	line = NULL;
	if (get_next_line(fd, &line) > 0 && g_ants == 0)
		ants(&line);
	while (get_next_line(fd,&line))
		checker_room(&line,room);
	start_(room);
}

int ants(char **line)
{
	int i;

	i = 0;
	if (**line == '-')
	{
		ft_putstr("Error");
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

int start_end(t_room **room, char **line)
{
	if (ft_strstr(*line,"##start"))
	{
		g_start_or_end = 1;
		ft_strdel(line);
		return (1);
	}
	else if (ft_strstr(*line,"##end"))
	{
		g_start_or_end = 2;
		ft_strdel(line);
		return (1);
	}
	else if (ft_strstr(*line,"#"))
	{
		g_start_or_end = 0;
		ft_strdel(line);
		return (1);
	}
	return (0);
}

int s_e_choose(void)
{
	int i;

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


int checker_room(char **line, t_room **room)
{
	char	**buff;

	if (start_end(room,line))
		return (1);
	buff = ft_strsplit(*line,' ');
	if (ft_strstr(*line,"-"))
	{
		linker(room, line);
		ft_strdel(line);
		return (1);
	}
	room_validator(buff);
	room_coords_validator(room,buff);
	working_with_room(buff,room,s_e_choose());
	while (*buff != NULL)
	{
		ft_strdel(buff);
		buff++;
	}
	ft_strdel(line);
	return (0);
}

void working_with_room(char **buff, t_room **room, int s_e)
{
	t_room *tmp;
	t_room *prev;

	if (*room == NULL)
	{
		(*room) = (t_room *)ft_memalloc(sizeof(t_room));
		(*room)->name = ft_strdup(buff[0]);
		(*room)->coord_x = ft_atoi(buff[1]);
		(*room)->coord_y = ft_atoi(buff[2]);
		(*room)->start_end = s_e;
	}
	else
	{
		tmp = (*room);
		while (tmp->next != NULL)
			tmp = tmp->next;
		prev = tmp;
		tmp->next = (t_room *)ft_memalloc(sizeof(t_room));
		tmp = tmp->next;
		tmp->prev = prev;
		tmp->name = ft_strdup(buff[0]);
		tmp->coord_x = ft_atoi(buff[1]);
		tmp->coord_y = ft_atoi(buff[2]);
		tmp->start_end = s_e;
	}
}

void room_validator(char **buff)
{
	int i;

	i = 0;
	count_quant_coords(buff);
	while (buff[1][i] != '\0')
	{
		if (!ft_isdigit(buff[1][i]))
		{
			ft_putstr("Error, bad coordinates x\n");
			exit(0);
		}
		i++;
	}
	i = 0;
	while (buff[2][i] != '\0')
	{
		if (!ft_isdigit(buff[2][i]))
		{
			ft_putstr("Error, bad coordinates y\n");
			exit(0);
		}
		i++;
	}
}

void count_quant_coords(char **buff)
{
	int i;

	i = 0;
	while (buff[i] != NULL)
		i++;
	if (i != 3)
	{
		ft_putstr("Error, room manage failed\n");
		exit(0);
	}
}

void room_coords_validator(t_room **room, char **buff)
{
	t_room *tmp;

	tmp = (*room);
	while (tmp != NULL)
	{
		if (tmp->coord_x == ft_atoi(buff[1]) && tmp->coord_y == ft_atoi(buff[2]))
		{
			ft_putstr("Error, invalid room coordinates, program terminated.\n");
			exit(0);
		}
		tmp = tmp->next;
	}
}