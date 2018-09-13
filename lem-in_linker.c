/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in_linker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:32:11 by ablizniu          #+#    #+#             */
/*   Updated: 2018/08/16 22:32:12 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void linker(t_room **room, char **line)
{
	char **buff;
	t_room *tmp;
	t_room *link;

	tmp = (*room);
	link = (*room);
	buff = ft_strsplit(*line,'-');
	checker_links(room,buff);
	while (ft_strcmp(tmp->name,buff[0]) != 0)
		tmp = tmp->next;
	while (ft_strcmp(link->name,buff[1]) != 0)
		link = link->next;
	create_links(tmp,link,buff,room);
}

void checker_links(t_room **room, char **buff)
{
	if (ft_strcmp(buff[0],buff[1]) == 0)
	{
		ft_putstr("Error, bad links\n");
		exit(0);
	}
}

int len_list(t_room **room)
{
	t_room *tmp;
	int i;

	i = 0;
	tmp = (*room);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_room *search_link(t_room **room, char *name)
{
	t_room *tmp;

	tmp = (*room);
	while (tmp)
	{
		if (ft_strcmp(tmp->name,name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void create_links(t_room *link1, t_room *link2, char **buff, t_room **room)
{
	int i;

	i = 0;
	if (link1->link == NULL)
		link1->link = (t_room *)ft_memalloc(sizeof(t_room) * len_list(room));
	if (link2->link == NULL)
		link2->link = (t_room *)ft_memalloc(sizeof(t_room) * len_list(room));
	while (link1->link[i].name != NULL)
		i++;
	link1->link[i] = *search_link(room,buff[1]);
	i = 0;
	while (link2->link[i].name != NULL)
		i++;
	link2->link[i] = *search_link(room,buff[0]);
}