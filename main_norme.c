/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:38:58 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:38:59 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				checker_room(char **line, t_room **room)
{
	char		**buff;

	if (start_end(line))
		return (1);
	buff = ft_strsplit(*line, ' ');
	if (ft_strstr(*line, "-"))
	{
		linker(room, line);
		ft_strdel(line);
		delete_buff(buff, 2);
		return (1);
	}
	if (room_validator(buff) == 0)
	{
		delete_buff(buff, 2);
		ft_strdel(line);
		return (0);
	}
	room_coords_validator(room, buff);
	working_with_room(buff, room, s_e_choose());
	delete_buff(buff, 3);
	ft_strdel(line);
	return (1);
}

void			delete_buff(char **buff, int len)
{
	int			i;

	i = 0;
	while (i < len && buff[i])
	{
		if (buff[i])
			ft_strdel(&buff[i]);
		i++;
	}
	free(buff);
}

void			working_with_room(char **buff, t_room **room, int s_e)
{
	t_room		*tmp;
	t_room		*prev;

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

int				room_validator(char **buff)
{
	int			i;

	i = 0;
	if (!count_quant_coords(buff))
		return (0);
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
	return (1);
}

int				count_quant_coords(char **buff)
{
	int			i;

	i = 0;
	while (buff[i] != NULL)
		i++;
	if (i != 3)
		return (0);
	return (1);
}
