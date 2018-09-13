/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 19:02:14 by ablizniu          #+#    #+#             */
/*   Updated: 2018/05/01 14:53:34 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char base_str(intmax_t c, int up)
{
	if (c < 0)
		c = c * (-1);
	if (c >= 0 && c <= 9)
		return ((char)(c + 48));
	if ( c >= 10 && c <= 16)
	{
		if (up)
			return ((char)(c + 65 - 10));
		else
			return ((char)(c + 97 - 10));
	}
	return (0);
}

int x_X_zero_width(t_alist **tmp,size_t l, char *str)
{
	char s[(*tmp)->j];
	
	s[(*tmp)->j] = '\0';
	if (((*tmp)->j) > l && (g_flags & zero) && !(g_flags & minus))
	{
		(g_flags & X) ? ((s[0] = '0') && (s[1] = 'X')) : (0);
		(g_flags & x) ? ((s[0] = '0') && (s[1] = 'x')) : (0);
		(*tmp)->j -= 2;
		ft_bchr(&s[2], '0', (*tmp)->j - l);
		ft_memcpy(&s[(*tmp)->j], str, l);
		g_flags = 0;
		buffering(tmp,0,(*tmp)->j + l,&s[0]);
		return (1);
		
	}
	return (0);
}

int x_X_precision(t_alist **tmp,size_t l, char *str, int *res)
{
	char s[(*tmp)->k];
	
	s[(*tmp)->k] = '\0';
	if ((*tmp)->k > l && (*tmp)->k > 0 && *str)
	{
		ft_bchr(&s[0],'0',((*tmp)->k > l) ? ((*tmp)->k - l) : (0));
		ft_memcpy(&s[((*tmp)->k > l) ? ((*tmp)->k - l) : (0)],str,l);
		s[(*tmp)->k + l] = '\0';
		buffering(tmp,0,(*tmp)->k,s);
		*res = 1;
		return (1);
	}
	else if ((*tmp)->k <= l && *str)
	{
		buffering(tmp, 0, l, str);
		*res = 1;
		return (1);
	}
	*res = 0;
	return (0);
}

int o_O_precision(t_alist **tmp,size_t l, char *str, int *res)
{
	char s[(*tmp)->k];
	
	s[(*tmp)->k] = '\0';
	if ((*tmp)->k > l && (*tmp)->k > 0 && *str)
	{
		ft_bchr(&s[0],'0',((*tmp)->k > l) ? ((*tmp)->k - l) : (0));
		ft_memcpy(&s[((*tmp)->k > l) ? ((*tmp)->k - l) : (0)],str,l);
		s[(*tmp)->k + l] = '\0';
		buffering(tmp,0,(*tmp)->k,s);
		*res = 1;
		return (1);
	}
	else if ((*tmp)->k <= l && *str)
	{
		buffering(tmp, 0, l, str);
		*res = 1;
		return (1);
	}
	*res = 0;
	return (0);
}

int S_s_precision(t_alist **tmp,size_t l, char *str)
{
	if ((*tmp)->k > l && *str)
	{
		buffering(tmp, 0, l, str);
		return (1);
	}
	else if ((g_flags & presicions) && (*tmp)->k <= l && *str)
	{
		buffering(tmp, 0, (*tmp)->k, str);
		return (1);
	}
	else if (!(g_flags & presicions) && *str)
	{
		buffering(tmp, 0, l, str);
		return (1);
	}
	else
		buffering(tmp,0,0," ");
	return (0);
}

void d_D_i_presisions(t_alist **tmp, size_t l, char *str, int *res)
{
	char s[(*tmp)->k + 2];
	
	s[(*tmp)->k] = '\0';
	if ((*tmp)->k > l && *str != '-')
	{
		ft_bchr(s, '0', (*tmp)->k - l);
		ft_memcpy(&s[(*tmp)->k - l],str,l);
		*res += 1;
		buffering(tmp,1,(*tmp)->k,s);
	}
	else if ((*tmp)->k >= l && *str == '-')
	{
		str++;
		s[0] = '-';
		ft_bchr(&s[1], '0', (*tmp)->k - l + 1);
		ft_memcpy(&s[(*tmp)->k - l + 2],str,l);
		*res += 1;
		buffering(tmp,1,(*tmp)->k + 1,s);
	}
}

void u_U_presisions(t_alist **tmp, size_t l, char *str, int *res)
{
	char s[(*tmp)->k];
	
	s[(*tmp)->k] = '\0';
	if ((*tmp)->k > l)
	{
		ft_bchr(s, '0', (*tmp)->k - l);
		ft_memcpy(&s[(*tmp)->k - l],str,l);
		*res += 1;
		buffering(tmp,1,(*tmp)->k,s);
	}
}

inline int hash_(t_alist **tmp, size_t l, char *str)
{
	int res;
	
	res = 0;
	(g_flags & hash && (g_flags & O || g_flags & o)) ? (hash_and_presic_o_O(tmp,l,&str[0]), (res++)) : (0);
	(g_flags & hash && (g_flags & X || g_flags & x)) ? (hash_and_presic_x_X(tmp,l,&str[0]), (res++)) : (0);
	((g_flags & presicions)) && (g_flags & X || g_flags & x) ? ((x_X_precision(tmp,l,str,&res))) : (0);
	((g_flags & presicions) && (g_flags & O || g_flags & o)) ? ((o_O_precision(tmp,l,str, &res))) : (0);
	((g_flags * presicions) && (g_flags & d || g_flags & i || g_flags & D)) ? (d_D_i_presisions(tmp, l, str,&res)) : (0);
	((g_flags * presicions) && (g_flags & u || g_flags & U)) ? (u_U_presisions(tmp, l, str,&res)) : (0);
	if (res != 0)
	{
		g_flags = 0;
		ft_bzero(str,l);
		return (1);
	}
	return (0);
}

int hash_and_presic_x_X(t_alist **tmp,size_t l, char *str)
{
	char s[(*tmp)->k + l + 2];
	
	s[(*tmp)->k + l + 2] = '\0';
	if ((g_flags & presicions) && ((*tmp)->k) > l)
	{
		((g_flags & hash) && (g_flags & X)) ? ((s[0] = '0') && (s[1] = 'X')) : (0);
		((g_flags & hash) && (g_flags & x)) ? ((s[0] = '0') && (s[1] = 'x')) : (0);
		ft_bchr(&s[2], '0', (*tmp)->k - l + 2);
		ft_memcpy(&s[(*tmp)->k - l + 2], str, l);
		s[(*tmp)->k + l] = '\0';
		buffering(tmp, 0, (size_t) (*tmp)->k + 2, &s[0]);
		return (1);
	}
	else if (x_X_zero_width(tmp,l,str))
		return (1);
	else if (*str)
	{
		(g_flags & X) ? ((s[0] = '0') && (s[1] = 'X')) : (0);
		(g_flags & x) ? ((s[0] = '0') && (s[1] = 'x')) : (0);
		ft_memcpy(&s[2],str,l);
		s[l + 2] = '\0';
		buffering(tmp,0,l + 2,&s[0]);
		return (1);
	}
	return (0);
}

inline int hash_and_presic_o_O(t_alist **tmp,size_t l, char *str)
{
	char s[(*tmp)->k + l + 2];
	
	s[(*tmp)->k + l + 2] = '\0';
	if ((g_flags & presicions) && ((*tmp)->k) > l)
	{
		(g_flags & hash) ? ((s[0] = '0')) : (0);
		ft_bchr(&s[1],'0',(*tmp)->k - l);
		ft_memcpy(&s[(*tmp)->k - l],str,l);
		s[(*tmp)->k + l] = '\0';
		buffering(tmp,0,(size_t)(*tmp)->k,&s[0]);
		return (1);
	}
	else
	{
		((g_flags & O)) ? ((s[0] = '0')) : (0);
		((g_flags & o)) ? ((s[0] = '0')) : (0);
		ft_memcpy(&s[1],str,l);
		s[l + 1] = '\0';
		buffering(tmp,0,l + 1,&s[0]);
		return (1);
	}
	return (0);
}

int zero_decimal_integer(t_alist **tmp, intmax_t n)
{
	size_t l;
	char s[2];
	
	l = 1;
	if (n == 0 && (*tmp)->k == 0 && !(*tmp)->j)
		(*tmp)->str += 1;
	else if (n == 0 && (*tmp)->k == 0 && (*tmp)->j)
	{
		buffering(tmp,0,1," ");
		(*tmp)->str += 1;
	}
	else
		(s[0] = '0', hash_(tmp, l, s));
	s[1] = '\0';
	(*tmp)->n = 0;
	return (1);
	
}

inline void ft_itoa_base_printf_s(intmax_t n, int base, int up,t_alist **tmp)
{
		int i;
		signed long long int num;
		char str[lenght((uintmax_t)n,base) + 2];
		
		i = 0;
		num = n;
		if (n == 0)
		{
			(g_flags & presicions) ? (zero_decimal_integer(tmp,n)) : (buffering(tmp,1,1,"0"));
			return ;
		}
		while(num != 0)
		{
			str[i] = base_str(num % base,up);
			num /= base;
			i++;
		}
		if (n < 0 && base == 10)
			str[i++] = '-';
		str[i] = '\0';
		swap(str,ft_strlen(str));
		if (hash_(tmp,ft_strlen(str),str))
			return ;
		buffering(tmp,1,ft_strlen(&str[0]),&str[0]);
}

