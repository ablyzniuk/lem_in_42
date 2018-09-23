/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norme_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:39:24 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/23 12:39:25 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			room_coords_validator(t_room **room, char **buff)
{
	t_room		*tmp;

	tmp = (*room);
	while (tmp != NULL)
	{
		if (tmp->coord_x == ft_atoi(buff[1])
			&& tmp->coord_y == ft_atoi(buff[2]))
		{
			ft_putstr("Error, invalid room coordinates, program terminated.\n");
			exit(0);
		}
		tmp = tmp->next;
	}
}
