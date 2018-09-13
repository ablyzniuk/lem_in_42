/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 22:24:43 by ablizniu          #+#    #+#             */
/*   Updated: 2018/04/21 19:40:07 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void fill_bits_a(t_alist **tmp)
{
	
	(*(*tmp)->str == '#') ? ((g_flags = g_flags | hash) && (*tmp)->str++) : (0);
	(*(*tmp)->str == '0') ? ((g_flags = g_flags | zero) && (*tmp)->str++) : (0);
	(*(*tmp)->str == '+') ? ((g_flags = g_flags | plus) && (*tmp)->str++) : (0);
	(*(*tmp)->str == '-') ? ((g_flags = g_flags | minus) && (*tmp)->str++) : (0);
	(*(*tmp)->str == ' ') ? ((g_flags = g_flags | space) && (*tmp)->str++) : (0);
	(*(*tmp)->str == 'n') ? ((g_flags = g_flags | n)  && (*tmp)->str++) : (0);
	(*(*tmp)->str == '*') ? ((g_flags = g_flags | ptr) && (*tmp)->str++) : (0);
	(*(*tmp)->str == '$') ? ((g_flags = g_flags | dollar)  && (*tmp)->str++) : (0);
}

int fill_bits(t_alist **tmp)
{
	int ret;
	
	ret = 0;
	//fill_bits_a(tmp);
	(*(*tmp)->str == 'd') ? ((g_flags = g_flags | d) && ret++) : (0);
	(*(*tmp)->str == 'i') ? ((g_flags = g_flags | i) && ret++) : (0);
	(*(*tmp)->str == 's') ? ((g_flags = g_flags | s) && ret++) : (0);
	(*(*tmp)->str == 'o') ? ((g_flags = g_flags | o) && ret++) : (0);
	(*(*tmp)->str == 'p') ? ((g_flags = g_flags | p) && ret++) : (0);
	(*(*tmp)->str == 'x') ? ((g_flags = g_flags | x) && ret++) : (0);
	(*(*tmp)->str == 'c') ? ((g_flags = g_flags | c) && ret++) : (0);
	(*(*tmp)->str == 'C') ? ((g_flags = g_flags | C) && ret++) : (0);
	(*(*tmp)->str == 'u') ? ((g_flags = g_flags | u) && ret++) : (0);
	(*(*tmp)->str == 'D') ? ((g_flags = g_flags | D) && ret++) : (0);
	(*(*tmp)->str == 'S') ? ((g_flags = g_flags | S) && ret++) : (0);
	(*(*tmp)->str == 'O') ? ((g_flags = g_flags | O) && ret++) : (0);
	(*(*tmp)->str == 'U') ? ((g_flags = g_flags | U) && ret++) : (0);
	(*(*tmp)->str == 'X') ? ((g_flags = g_flags | X) && ret++) : (0);
	(*(*tmp)->str == 'b') ? ((g_flags = g_flags | b) && ret++) : (0);
	(*(*tmp)->str == 'B') ? ((g_flags = g_flags | B) && ret++) : (0);
	(*(*tmp)->str == 'k') ? ((g_flags = g_flags | k) && ret++) : (0);
	if (ret == 1)
		return (1);
	return (0);

}

int isflag(void)
{
	unsigned int a;
	
	a = 0;
	(g_flags & hh) ? (a += 1) : (0);
	(g_flags & h) ? (a += 1) : (0);
	(g_flags & l) ? (a += 1) : (0);
	(g_flags & ll) ? (a += 1) : (0);
	(g_flags & j) ? (a += 1) : (0);
	(g_flags & z) ? (a += 1) : (0);
    return (a);
}

int search(void)
{
	unsigned int a;
	
	a = 0;
	(g_flags & hh) ? (a = hh) : (0);
	(g_flags & h) ? (a = h) : (0);
	(g_flags & l) ? (a = l) : (0);
	(g_flags & ll) ? (a = ll) : (0);
	(g_flags & j) ? (a = j) : (0);
	(g_flags & z) ? (a = z) : (0);
	return (a);
}
