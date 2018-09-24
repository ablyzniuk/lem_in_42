/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_for_norme_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:46:27 by ablizniu          #+#    #+#             */
/*   Updated: 2018/09/24 17:46:30 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			norme_for_linker(int *arr, t_room **link1, t_room **link2)
{
	(*link1)->llr = arr[1];
	(*link1)->llr++;
	(*link2)->llr = arr[2];
	(*link2)->llr++;
}

void			one_(t_room *start, t_result **tmp)
{
	ft_putchar('\n');
	norm_for_l_a_3(start, tmp);
}
