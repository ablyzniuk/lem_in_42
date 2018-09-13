/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 21:57:50 by ablizniu          #+#    #+#             */
/*   Updated: 2018/05/05 17:07:08 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *format,...)
{
	va_list ag;
	static t_alist *tmp;
	int res;
	
	tmp = NULL;
	tmp = ft_alist_initialize(tmp,0);
	tmp->str = (char *)format;
	tmp->tmp_1 = (char *)format;
	tmp->i = 0;
	tmp->n = 0;
	tmp->k = 0;
	tmp->len_format = 0;
	tmp->extra = 0;
	ft_bzero(tmp->buff,BUFF_SIZE);
	va_start(ag,format);
	res = ft_printf_core(ag, tmp);
	va_end(ag);
	g_flags = 0;
	free(tmp);
	return (res);
}

int ft_fpritnf(const int fd,const char *format,...)
{
	va_list ag;
	static t_alist *tmp;
	int res;
	
	tmp = NULL;
	res = 0;
	tmp = ft_alist_initialize(tmp,0);
	tmp->fd = fd;
	ft_bzero(tmp->buff,BUFF_SIZE);
	va_start(ag,format);
	res = ft_printf_core(ag, tmp);
	va_end(ag);
	g_flags = 0;
	return (res);
}

inline int ft_printf_core(va_list ag, t_alist *tmp)
{
    while(*tmp->str)
    {
		g_flags = 0;
        if (*tmp->str == '%')
        {
	        tmp->str++;
            if(validator_specificators_and_flags(ag,&tmp))
                continue ;
        }
        buffering(&tmp,1,1,"");
    }
	if (!*tmp->str)
	{
		if (*tmp->buff)
		{
			(!*(tmp->buff) && (tmp->extra != 0) &&
					(tmp->size_bytes < tmp->extra)) ?
			(tmp->size_bytes = tmp->extra) : (0);
			output(tmp->fd, tmp->buff, tmp->size_bytes);
			return ((int) tmp->size_bytes);
		}
		(!*(tmp->buff) && (tmp->extra != 0) && (tmp->size_bytes < tmp->extra))
		? (tmp->size_bytes = tmp->extra) : (0);
		return ((int) tmp->size_bytes);
	}
	return 0;
}

//TODO сделать звезду - для фт-лс надо
//TODO значит - надо сделать фиксить юникод: спихнуть все в одну строку; фиксить # и х,Х пофиксить перезапись строки, чтобы она продлвалась, доделать точность и бонусы, и сдавай