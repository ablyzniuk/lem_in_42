/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_cor_norme_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 18:49:34 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/26 18:49:35 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				is_it_way(t_room **way)
{
	t_room		*tmp;
	int			start;
	int			end;

	start = 0;
	end = 0;
	tmp = (*way);
	while (tmp)
	{
		if (tmp->start_end == END)
			end++;
		if (tmp->start_end == START)
			start++;
		tmp = tmp->next;
	}
	if (start == 1 && end == 1)
		return (1);
	return (0);
}
