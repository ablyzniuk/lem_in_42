/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 20:21:53 by ablizniu          #+#    #+#             */
/*   Updated: 2018/04/27 22:36:41 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


inline int ft_printf_processing(va_list ap, t_alist **tmp)
{
	if (g_flags & d || g_flags & i)
	{
		d_i(tmp, ap);
		(g_flags & d) ? (g_flags ^= d) : (g_flags ^= i);
		return (1);
	}
	else if (g_flags & D)
	{
		ft_itoa_base_printf_s(va_arg(ap, long int), 10, 0,tmp);
		g_flags ^= D;
		return (1);
	}
	else if (g_flags & u)
	{
		u_u(tmp, ap);
		(g_flags  & u) ? (g_flags ^= u) : (0);
		return (1);
	}
	else if (g_flags & U)
	{
		ft_itoa_base_printf_u(va_arg(ap, unsigned long int), 10, 0,tmp);
		(*tmp)->str++;
		g_flags ^= U;
		return (1);
	}
	else if (g_flags & o)
	{
		o_t(tmp,ap);
		(*tmp)->str++;
		g_flags ^= o;
		return (1);
	}
	else if (g_flags & O)
	{
		ft_itoa_base_printf_s(va_arg(ap, long int), 8, 0,tmp);
		g_flags ^= O;
		return (1);
	}
	else if (g_flags & x)
	{
		x_hex(tmp,ap);
		(*tmp)->str++;
		g_flags ^= x;
		return (1);
	}
	else if (g_flags & X)
	{
		(isflag()) ? (ft_itoa_base_printf_u(isflags_unsigned(ap), 16, 1,tmp)) : (ft_itoa_base_printf_u(va_arg(ap, unsigned int), 16, 1,tmp));
		(*tmp)->str++;
		g_flags ^= X;
		return (1);
	}
	else if (g_flags & b)
	{
		b_binary(tmp,ap);
		g_flags ^= b;
		return (1);
	}
	else if (g_flags & B)
	{
		ft_itoa_base_printf_u(va_arg(ap, unsigned long int), 2, 0,tmp);
		g_flags ^= B;
		return (1);
	}
	else if (g_flags & p)
	{
		p_pointer_addres(tmp,ap);
		g_flags ^= p;
		return (1);
	}
	else if (g_flags & c)
	{
		c_character(tmp,ap);
		g_flags ^= c;
		return (1);
	}
	else if (g_flags & C)
	{
		unicode_C(tmp,ap);
		g_flags ^= C;
		return (1);
	}
	else if (g_flags & s)
	{
		s_string(tmp,ap);
		g_flags ^= s;
		return (1);
	}
	else if (g_flags & S)
	{
		unicode_S(tmp,ap);
		g_flags ^= S;
		return (1);
	}
	else if(g_flags & k)
	{
		k_time_date(tmp,ap);
		g_flags ^= k;
		return (1);
	}
	else if (*(*tmp)->str == '%')
	{
		buffering(tmp,0,(*tmp)->j,"");
	}
    return 0;
}

intmax_t isflags_signed(va_list ap)
{
    if (g_flags & hh || g_flags & h)
        return ((g_flags & h) ? ((short)(va_arg(ap,int))) : (char)((va_arg(ap,int))));
    else if (g_flags & l || g_flags & ll)
        return ((g_flags & ll) ? ((va_arg(ap,long long))) : ((va_arg(ap,long))));
    else if (g_flags & j)
        return (va_arg(ap,intmax_t));
    else if (g_flags & z)
        return (va_arg(ap,size_t));
    return (0);
}

uintmax_t isflags_unsigned(va_list ap)
{
    if (g_flags & hh || g_flags & h)
        return ((g_flags & h) ? ((unsigned short)(va_arg(ap,int))) : ((unsigned char)(va_arg(ap,int))));
    else if (g_flags & l || g_flags & ll)
        return ((g_flags & ll) ? ((va_arg(ap,unsigned long long))) : ((va_arg(ap,unsigned long))));
    else if (g_flags & j)
        return (va_arg(ap,uintmax_t));
    else if (g_flags & z)
        return ((uintmax_t)va_arg(ap,size_t));
	return (0);
}

void x_hex(t_alist **tmp, va_list ap)
{
	(isflag()) ? (ft_itoa_base_printf_u(isflags_unsigned(ap),16,0,tmp)) : (ft_itoa_base_printf_u(va_arg(ap,unsigned int),16,0,tmp));
}

void b_binary(t_alist **tmp, va_list ap)
{
	(isflag()) ? (ft_itoa_base_printf_u(isflags_unsigned(ap),2,0,tmp)) : (ft_itoa_base_printf_u(va_arg(ap,unsigned long int),2,0,tmp));
	(*tmp)->str++;
}

void d_i(t_alist **tmp, va_list ap)
{
	(isflag()) ? (ft_itoa_base_printf_s(isflags_signed(ap),10,0,tmp)) : (ft_itoa_base_printf_s(va_arg(ap,int),10,0,tmp));
}

void u_u(t_alist **tmp, va_list ap)
{
	(isflag()) ? (ft_itoa_base_printf_u(isflags_unsigned(ap),10,0,tmp)) : ( ft_itoa_base_printf_u(va_arg(ap,unsigned int),10,0,tmp));
	(*(*tmp)->str) ? ((*tmp)->str += 1) : (0);
}

void o_t(t_alist **tmp, va_list ap)
{
	(isflag()) ? (ft_itoa_base_printf_u(isflags_unsigned(ap),8,0,tmp)) : (ft_itoa_base_printf_u(va_arg(ap,unsigned int),8,0,tmp));
}

void p_pointer_addres(t_alist **tmp, va_list ap)
{
	void *p;
	
	buffering(tmp,1,2,"0x");
	p = (va_arg(ap, void *));
	(p) ? (ft_itoa_base_printf_u((uintmax_t)p, 16, 0,tmp)) : (buffering(tmp,0,1,"0"));
}

void c_character(t_alist **tmp, va_list ap)
{
	char f;
	
	if (search() == l)
	{
		unicode_C(tmp, ap);
		g_flags ^= l;
	}
	else
	{
		f = (char) va_arg(ap,unsigned int);
		(f == '\0') ? (c_EOF(tmp)) : (buffering(tmp,1,1,&f));
	}
}

void format_len(t_alist **tmp)
{
	while((*tmp)->tmp_1[(*tmp)->len_format] != '\0')
		(*tmp)->len_format++;
}

void c_EOF(t_alist **tmp)
{
	format_len(tmp);
	if ((*tmp)->j && width_c_EOF(tmp))
		return ;
	(*tmp)->size_bytes += 1;
	output((*tmp)->fd,(*tmp)->buff,(*tmp)->size_bytes);
	ft_bzero((*tmp)->buff,BUFF_SIZE);
	(*tmp)->extra = (*tmp)->size_bytes;
	(*tmp)->size_bytes = 0;
	(*tmp)->str += 1;
	if (*(*tmp)->str)
	{
		ft_memcpy((*tmp)->buff,(*tmp)->str,(ft_strchr((*tmp)->str,'%')) ? (ft_strchr((*tmp)->str,'%') - (*tmp)->str) : ((*tmp)->len_format - (*tmp)->extra));
		output((*tmp)->fd,(*tmp)->buff,(*tmp)->len_format - (*tmp)->extra - 1);
		ft_bzero((*tmp)->buff,BUFF_SIZE);
	}
}

int width_c_EOF(t_alist **tmp)
{
	char s[(*tmp)->j];

	s[(*tmp)->j] = '\0';
	if ((*tmp)->j > 1 && !(g_flags & zero))
	{
		ft_bchr(&s[0], ' ', (*tmp)->j);
		ft_memcpy((*tmp)->buff,s,(*tmp)->j - 1);
		output((*tmp)->fd,(*tmp)->buff,(*tmp)->j);
		ft_bzero((*tmp)->buff,BUFF_SIZE);
		(*tmp)->size_bytes += (*tmp)->j;
		(*tmp)->str += 1;
		return (1);
	}
	return (0);
}

void p_b_f(t_alist **tmp,int step, size_t size)
{
	buffering(tmp,step,size,"(null)\0");
	(*tmp)->str -= 1;
}

void s_string(t_alist **tmp, va_list ap)
{
	char *f;
	
	if (search() == l)
		unicode_S(tmp, ap);
	else
	{
		f = va_arg(ap,char *);
		(!f) ? (p_b_f(tmp,1,6)) : (S_s_precision(tmp,ft_strlen(f),f));
		(*tmp)->str += 1;
		g_flags ^= s;
	}
}

void k_time_date(t_alist **tmp, va_list ap)
{
	time_t timer;
	
	timer = time(NULL);
	(va_arg(ap,int) == 1) ? (buffering(tmp,1,24,ctime(&timer))) : (buffering(tmp,1,1,"0"));
	g_flags ^= k;
	
}