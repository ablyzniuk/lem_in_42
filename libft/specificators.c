/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specificators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 16:04:00 by ablizniu          #+#    #+#             */
/*   Updated: 2018/04/21 19:23:03 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* создать функции для спецификаторов, создать файлы парса флагов и записи в биты, разбить парс спецификаторов и флагов в разные функции */

inline int validator_specificators_and_flags(va_list ap, t_alist **tmp)
{
    while ((*tmp)->str && *(*tmp)->str && *(*tmp)->str != '%' && !fill_bits(tmp))
    {
	    width(tmp);
	    presic_(tmp);
	    fill_bits_a(tmp);
	    validator_flags(tmp);
    }
    (ft_printf_processing(ap, tmp));
    return (1);
}

//TODO добавь функция обработки, как только ты после первого процента обработал спецификатор ретурном выходи и ищи следующий
//TODO  если нет спецификатора но есть флаг выводи пустое место


void validator_flags(t_alist **tmp)
{
	if(*(*tmp)->str == 'h' && *((*tmp)->str + 1 ) == 'h')
    {
        if (!g_flags)
            g_flags = g_flags | hh;
        else if (g_flags < hh)
        {
	        g_flags |= hh;
        }
        (*tmp)->str += 2;
        return ;
    }
	else if (*(*tmp)->str == 'h')
    {
        if (!g_flags)
            g_flags = g_flags | h;
        else if (g_flags < h)
        {
	        g_flags ^= search();
	        g_flags |= h;
        }
	    (*tmp)->str++;
        return ;
    }
	else if (*(*tmp)->str == 'l' && *((*tmp)->str + 1) == 'l')
    {
        if (!g_flags)
            g_flags = g_flags | ll;
        else if (g_flags < ll)
        {
	        g_flags ^= search();
	        g_flags |= ll;
        }
        (*tmp)->str++;
        return ;
    }
	else if (*(*tmp)->str == 'l')
	{
        if (!g_flags)
            g_flags = g_flags | l;
        else if (g_flags < l)
        {
	        g_flags ^= search();
	        g_flags |= l;
        }
		(*tmp)->str++;
        return ;
	}
//	if (validator_flags_2(tmp))
//		return ;
//	(*tmp)->str += 1;
	validator_flags_2(tmp);
}

int validator_flags_2(t_alist **tmp)
{
    if(*(*tmp)->str == 'j')
    {
        if (!g_flags)
            g_flags = g_flags | j;
        if(g_flags < j)
        {
	        g_flags ^= search();
	        g_flags |= j;
        }
	    (*tmp)->str++;
        return (1);
    }
    else if (*(*tmp)->str == 'z')
    {
        if (!g_flags)
            g_flags = g_flags | z;
        else if (g_flags < z)
        {
	        g_flags ^= search();
            g_flags |= z;
        }
	    (*tmp)->str++;
        return (1);
    }
	return (0);
}



