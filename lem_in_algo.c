/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 16:50:40 by ablizniu          #+#    #+#             */
/*   Updated: 2018/08/21 16:50:42 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void search_the_way(t_room **room, t_room **way)
{
	t_room *tmp;

	tmp = (*room);
	while (tmp->start_end != END)
		tmp = tmp->next;
	while (tmp->start_end != START)
	{
		add_to_the_way(room,tmp,way);
		tmp = sort_links(room, tmp);
		if (tmp == NULL)
		{
			if ((tmp = is_way(room)) != NULL);
			else
				break;
		}
		if (tmp->start_end != START)
			tmp->status = 1;
	}
	if (tmp != NULL)
		add_to_the_way(room,tmp,way);
}

t_room *sort_links(t_room **room, t_room *obj)
{
	t_room *buff;
	t_room *tmp;
	int safe;
	int i;

	i = 0;
	buff = NULL;
	safe = obj->distance_from_start;
	while (obj->link[i].name != NULL)
	{
		tmp = que_search(room, obj->link[i].name);
		if (tmp->status == 0)
		{
			if ((tmp->distance_from_start < obj->distance_from_start))
			{
				buff = tmp;
				i++;
				continue ;
			}
			else if (tmp->distance_from_start > obj->distance_from_start && buff == NULL && tmp->start_end != END)
			{
				i = 0;
				obj->distance_from_start++;
				continue ;
			}
		}
		i++;
	}
	obj->distance_from_start = safe;
	return (buff);
}

t_room *is_way(t_room **room)
{
	int i;
	t_room *tmp;
	t_room *buff;

	i = 0;
	tmp = (*room);
	while (tmp->start_end != END)
		tmp = tmp->next;
	while (tmp->link[i].name != NULL)
	{
		buff = que_search(room,tmp->link[i].name);
		if (buff->status == 0)
			return (buff);
		i++;
	}
	return (NULL);
}

void add_to_the_way(t_room **room, t_room *tmp, t_room **way)
{
	t_room *temp;
	t_room *buff;
	t_room *prev;

	buff = que_search(room,tmp->name);
	if ((*way) == NULL)
	{
		(*way) = (t_room *)ft_memalloc(sizeof(t_room));
		(*way)->status = buff->status;
		(*way)->start_end = buff->start_end;
		(*way)->name = ft_strdup(buff->name);
	}
	else
	{
		temp = (*way);
		while (temp->next != NULL)
			temp = temp->next;
		prev = temp;
		temp->next = (t_room *)ft_memalloc(sizeof(t_room));
		temp = temp->next;
		temp->prev = prev;
		temp->status = buff->status;
		temp->start_end = buff->start_end;
		temp->name = ft_strdup(buff->name);
	}
}

void processing_of_the_ways(t_room **room, t_result **result)
{
	t_room *way;
	t_room *tmp;
	int len;

	way = NULL;
	len = 0;
	search_the_way(room, &way);
	tmp = way;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	making_final_results(way,result,len);

}

void swap_list_elem(t_room *room, int len)
{
	t_room *tmp_1;
	t_room *tmp_2;
	char *buff;
	int start_end;

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

void  distribution_of_ants(t_room **room)
{
	t_room		*tmp;
	t_result	*resulted_ways;
	int i;

	i = 0;
	tmp = (*room);
	resulted_ways = NULL;
	while (tmp && tmp->start_end != END)
		tmp = tmp->next;
	while (tmp && tmp->link[i].name != NULL)
	{
		processing_of_the_ways(room,&resulted_ways);
		i++;
	}
	g_key = 2;
	if (g_key == 1)
		key_bonus(&resulted_ways);
	if (g_key == 2)
	{
		key_2_bonus(&resulted_ways);
		output_key_2_bonus(&resulted_ways);
	}
	distribution(room,&resulted_ways);
}

void key_2_bonus(t_result **resulted_ways)
{
	int i;
	t_result *tmp;
	int min_len;

	i = g_ants;
	tmp = (*resulted_ways);
	min_len = (*resulted_ways)->len_of_the_way;
	while (i)
	{
		while (tmp)
		{
			if (i - min_len >= tmp->len_of_the_way - min_len && i)
			{
				tmp->quant_of_ant++;
				i--;
			}
			else if (i - min_len < tmp->len_of_the_way - min_len && i)
			{
				(tmp = key_2_bonus_find_min(resulted_ways))->quant_of_ant++;
				i--;
			}
			tmp = tmp->next;
		}
		tmp = (*resulted_ways);
	}
}

void output_key_2_bonus(t_result **result)
{
	t_result *tmp;
	int i;

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
}

t_result *key_2_bonus_find_min(t_result **result)
{
	t_result *tmp;
	t_result *buff;

	tmp = (*result);
	buff = tmp;
	while (tmp->next)
	{
		if (tmp->quant_of_ant < buff->quant_of_ant && tmp->len_of_the_way <= buff->len_of_the_way)
			buff = tmp;
		tmp = tmp->next;
	}
	return (buff);
}

void key_bonus(t_result **resulted_ways)
{
	t_result *tmp;
	t_room *tmp_r;
	int i;

	i = 1;
	tmp = *resulted_ways;
	ft_putstr("\tWAYS FOR OUTPUT\n\n");
	while (tmp)
	{
		tmp_r = tmp->link_arr;
		ft_putstr("Way number: ");
		ft_putnbr(i);
		ft_putstr(" | Length: ");
		ft_putnbr(tmp->len_of_the_way);
		ft_putstr(" | ");
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

void bonus(t_room *room)
{
	ft_putstr(room->name);
	if (room->next)
		ft_putstr("<-");
}

void reverse_list(t_result **result)
{
	t_result *tmp;

	tmp = (*result);
	while (tmp)
	{
		tmp->quant_of_ant = 0;
		error_no_conditons_for_algo(tmp->link_arr);
		swap_list_elem(tmp->link_arr,tmp->len_of_the_way);
		tmp = tmp->next;
	}

}


void distribution(t_room **room, t_result **resulted_ways)
{
	int min_len;
	t_result *tmp;
	int n;

	n = 0;
	min_len = (*resulted_ways)->len_of_the_way;
	tmp = (*resulted_ways);
	zero_status(resulted_ways);
	reverse_list(resulted_ways);
	while (is_ant(*resulted_ways))
	{
		while (tmp)
		{
			if (g_ants - min_len >= tmp->len_of_the_way - min_len && g_ants)
			{
				if (ants_distrib(&tmp->link_arr, &n))
					tmp->quant_of_ant++;
			}
			else if (g_ants - min_len < tmp->len_of_the_way - min_len && g_ants)
			{
				if (ants_distrib(&(key_2_bonus_find_min(resulted_ways))->link_arr, &n))
					(key_2_bonus_find_min(resulted_ways))->quant_of_ant++;
			}
			tmp = tmp->next;
		}
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
	free_room(room);
	free_ways(resulted_ways);
}

void free_ways(t_result **result)
{
	t_result *buff;

	while (*result)
	{
		buff = (*result);
		free_room(&buff->link_arr);
		(*result) = (*result)->next;
		ft_memdel((void *)&buff);
	}
	ft_memdel((void **)result);
}


void free_room(t_room **room)
{
	t_room *buff;

	while (*room)
	{
		buff = (*room);
		(*room) = (*room)->next;
		ft_strdel(&buff->name);
		if (buff->link)
			ft_memdel((void *)&buff->link);
		ft_memdel((void *)&buff);
	}
	ft_memdel((void **)room);
}

void bzero_output(t_result **result)
{
	t_result *tmp;
	t_room *tmp_r;

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

int is_ant(t_result *result)
{
	t_result *tmp;
	t_room *tmp_r;

	tmp = result;
	while (tmp)
	{
		tmp_r = tmp->link_arr;
		while (tmp_r)
		{
			if ((tmp_r->what_ant != 0 && tmp_r->status != 0) || g_ants > 0)
				return (1);
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void output(t_result **result)
{
	t_result *tmp;
	t_room *tmp_r;

	tmp = *result;
	while (tmp)
	{
		tmp_r = rotate_to_end(tmp->link_arr);
		while (tmp_r)
		{
			if (tmp_r->status && tmp_r->what_ant && !tmp_r->output)
			{
				que_for_output(*tmp_r);
				tmp_r->output = 1;
				if (tmp_r->start_end == END)
				{
					tmp_r->what_ant = 0;
					tmp_r->what_ant = 0;
					tmp_r->status = 0;
					tmp_r->output = 1;
				}
				break ;
			}
			tmp_r = tmp_r->prev;
		}
		tmp = tmp->next;
	}
}

void all_push(t_result **result)
{
	t_result *tmp;
	t_room *r;

	tmp = (*result);
	while (tmp)
	{
		r = rotate_to_end(tmp->link_arr);
		while (r)
		{
			if (r->start_end != END && r->what_ant && r->status)
			{
				r->output = 0;
				push_ants(r);
			}
			r = r->prev;
		}
		tmp = tmp->next;
	}
}

int not_outputed(t_result **result)
{
	t_result *tmp;
	t_room *room;

	tmp = (*result);
	while (tmp)
	{
		room = tmp->link_arr;
		while (room)
		{
			if (room->what_ant != 0 && room->output == 0)
				return (1);
			room = room->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

t_room *rotate_to_end(t_room *room)
{
	while (room->next != NULL)
		room = room->next;
	return (room);
}

void push_ants(t_room *room)
{
	t_room *tmp_current;
	t_room *tmp_next;

	tmp_current = room;
	if (room->next)
		tmp_next = room->next;
	else
		return ;
	tmp_next->what_ant = tmp_current->what_ant;
	tmp_next->status = 1;
	tmp_current->what_ant = 0;
	tmp_current->status = 0;
}

int ants_distrib(t_room **room, int *ant)
{
	t_room *tmp;

	tmp = (*room);
	if (tmp->start_end == START)
		tmp = tmp->next;
	if (tmp->status == 0 && tmp->what_ant == 0 && g_ants > 0)
	{
		tmp->status = 1;
		(*ant)++;
		g_ants--;
		tmp->output = 0;
		tmp->what_ant = *ant;
		return (1);
	}
	return (0);
}

void que_for_output(t_room elem)
{
	ft_putchar('L');
	ft_putnbr(elem.what_ant);
	ft_putchar('-');
	ft_putstr(elem.name);
	ft_putchar(' ');
}

void zero_status(t_result **resulted_ways)
{
	t_result *tmp;
	t_room *tmp_r;

	tmp = (*resulted_ways);
	while (tmp != NULL)
	{
		tmp_r = tmp->link_arr;
		while (tmp_r)
		{
			tmp_r->status = 0;
			tmp_r = tmp_r->next;
		}
		tmp = tmp->next;
	}
}
