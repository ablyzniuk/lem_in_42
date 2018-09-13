/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_core_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:20:16 by ablizniu          #+#    #+#             */
/*   Updated: 2018/05/07 14:13:03 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline void unicode_0(t_alist **tmp, unsigned int value)
{
	char f;
	
	f = (char )value;
	buffering(tmp,0,1,&f);
}

inline void unicode_1(t_alist **tmp, unsigned int value)
{
	unsigned char octet[4][1];
	unsigned int o_m[4];
	unsigned char res[2];
	
	o_m[1] = (value & 0x3f);
	o_m[0] = ((value >> 6) & 0x3f);
	res[1] = '\0';
	octet[0][0] = (unsigned char)((second >> 8) | o_m[0]);
	ft_memcpy(&res[0],(void *)octet[0],1);
	octet[1][0] = (unsigned char) ((second & 0x80) | o_m[1]);
	ft_memcpy(&res[1],(void *)octet[1],1);
	buffering(tmp,0,2,(char *)&res[0]);
}

inline void unicode_2(t_alist **tmp,unsigned int value)
{
	unsigned char octet[4][1];
	unsigned int o_m[4];
	unsigned char res[3];
	
	o_m[0] = (value & 0x3f);
	o_m[1] = (value >> 6) & 0x3f;
	o_m[2] = (value >> 12) & 0x3f;
	octet[0][0] = (unsigned char)((third >> 16) | o_m[2]);
	ft_memcpy(&res[0],(void *)octet[0],1);
	octet[1][0] = (unsigned char)(((third >> 8) & 0x80) | o_m[1]);
	ft_memcpy(&res[1],(void *)octet[1],1);
	octet[2][0] = (unsigned char)(((third & 0x80) | o_m[0]));
	ft_memcpy(&res[2],(void *)octet[2],1);
	buffering(tmp,0,3,(char *)&res[0]);
}

inline void unicode_3(t_alist **tmp, unsigned int value)
{
	unsigned char octet[4][1];
	unsigned int o_m[4];
	unsigned char res[4];

	o_m[0] = (value & 0x3f);
	o_m[1] = (value >> 6) & 0x3f;
	o_m[2] = (value >> 12) & 0x3f;
	o_m[3] = (value >> 20) & 0x7;
	octet[0][0] = (unsigned char)((fourth >> 24) | o_m[3]);
	ft_memcpy(&res[0],(void *)octet[0],1);
	octet[1][0] = (unsigned char)(((fourth >> 16) & 0x80) | o_m[2]);
	ft_memcpy(&res[1],(void *)octet[1],1);
	octet[2][0] = (unsigned char)(((fourth >> 8) & 0x80) | o_m[1]);
	ft_memcpy(&res[2],(void *)octet[2],1);
	octet[3][0] = (unsigned char)((fourth & 0x80) | o_m[0]);
	ft_memcpy(&res[3],(void *)octet[3],1);
	buffering(tmp,0,4,(char *)&res[0]);
	
}


inline void unicode_C(t_alist **tmp, va_list ap)
{
	wchar_t val;
	unsigned int value;
	
	val = (va_arg(ap,wchar_t));
	value = (unsigned int )val;
	(value <= 0x80) ? (unicode_0(tmp,value)) : (0);
	(value > 0x80 && value <= 0x800) ? (unicode_1(tmp,value)) : (0);
	(value > 0x800 && value <= 0xFFFF) ? (unicode_2(tmp,value)) : (0);
	(value > 0xFFFF) ? (unicode_3(tmp,value)) : (0);
	(*tmp)->str++;
}

inline void unicode_S(t_alist **tmp, va_list ap)
{
	wchar_t *s_t;
	unsigned int value;
	
	if(!(s_t = va_arg(ap,wchar_t *)))
	{
		buffering(tmp,1,6,"(null)");
		g_flags ^= s;
		g_flags ^= l;
		return ;
	}
	while(*s_t)
	{
		value = (unsigned int) *s_t;
		(value <= 0x80) ? (unicode_0(tmp,value)) : (0);
		(value > 0x80 && value <= 0x800) ? (unicode_1(tmp,value)) : (0);
		(value > 0x800 && value <= 0x8000) ? (unicode_2(tmp,value)) : (0);
		(value > 0x8000) ? (unicode_3(tmp,value)) : (0);
		s_t++;
	}
	g_flags ^= s;
	g_flags ^= l;
	(*tmp)->str++;
}

/*-----------------------------------******---------------------*/

void width(t_alist **tmp)
{
	(*tmp)->j = 0;
	if (*(*tmp)->str >= '1')
		(*tmp)->j = (size_t)ft_atoi((*tmp)->str);
	else if (*(*tmp)->str == '0')
	{
		g_flags |= zero;
		(*tmp)->str++;
		return ;
	}
	while (*(*tmp)->str >= '0' && *(*tmp)->str <= '9')
		(*tmp)->str++;
}

int presic_(t_alist **tmp)
{
	(*tmp)->k = 0;
	if (*(*tmp)->str == '.')
	{
		(*tmp)->str++;
		(*tmp)->k = (size_t)ft_atoi((*tmp)->str);
		while (*(*tmp)->str >= '0' && *(*tmp)->str <= '9')
			(*tmp)->str++;
		g_flags |= presicions;
	}
	return 0;
}

/*-----------------------------------******---------------------*/

inline void min_(t_alist **tmp, char **symbol, size_t *size, char *str)
{
	(!(g_flags & minus)) ? (w_m(tmp,size,symbol,str)) : (ft_bchr(str,' ',(size_t)(*tmp)->j));
}

inline void w_m(t_alist **tmp, size_t *size, char **symbol, char *str)
{

	while (((*tmp)->j > *size))
	{
		(g_flags & zero) ? (p_m(tmp,symbol,size,str)) : (str[(*tmp)->n] = ' ');
		(*tmp)->n++;
		(*tmp)->j--;
	}
	(*tmp)->n = 0;
}

inline void p_m(t_alist **tmp, char **symbol, size_t *size, char *str)
{
	if (!(g_flags & presicions))
		(**symbol == '-') ? ((ft_memcpy(str, "-", 1)) && (*symbol)++  && (*size -= 1)) : (void)(ft_memcpy(&str[(*tmp)->n], "0", 1));
	else if ((g_flags & presicions))
		str[(*tmp)->n] = ' ';
}

/*-----------------------------------******---------------------*/

void plus_(t_alist **tmp, char **symbol, char *str)
{
	if ((*str != '-') && (**symbol != '-') && (g_flags & plus) && (g_flags & zero))
		str[0] = '+';
	if ((g_flags & plus) && (**symbol != '-') && !(g_flags & zero) && !(g_flags & minus) && *str)
		str[ft_strlen(str) - 1] = '+';
	if ((g_flags & plus) && !(g_flags & zero) && (g_flags & minus) && (**symbol != '-'))
		str[0] = '+';
	else if((g_flags & plus) &&(**symbol != '-') && (g_flags & minus))
	{
		str[0] = '+';
		((*tmp)->j) ? ((*tmp)->j--) : (0);
	}
	else if((g_flags & plus) && (**symbol != '-') && *str != '-' && !(g_flags & zero) && !(*tmp)->j)
	{
		str[0] = '+';
		((*tmp)->j) ? ((*tmp)->j--) : (0);
	}
}

void space_(t_alist **tmp, char *str, char *symbol)
{
	char s[(*tmp)->n + 1];
	
	s[(*tmp)->n + 1] = '\0';
	if (g_flags & space && !(*tmp)->j && !(g_flags & plus) && *symbol != '-' && !(g_flags & u || g_flags & U))
	{
		s[0] = ' ';
		ft_memcpy(&s[1],str,(*tmp)->n);
		ft_memcpy(str,s,(*tmp)->n + 1);
		(*tmp)->n  += 1;
		return ;
	}
}


inline void buffering(t_alist **tmp, int step, size_t size, char *symbol)
{
	char s[(*tmp)->j + size + 1];

	s[(*tmp)->j + size + 1] = '\0';
	ft_bzero(&s[0],(*tmp)->j + size + 1);
	if (!*symbol)
	{
		(*tmp)->size_bytes = buff_len +  (*tmp)->extra;
		pre_output1(tmp,&size);
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes],(*tmp)->str, size);
		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
	}
	else
	{
		min_(tmp,&symbol,&size,&s[0]);
		plus_(tmp,&symbol,&s[0]);
		(*tmp)->n = ft_strlen(&s[0]);
		pre_output2(tmp, size, &s[0], symbol);
 		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
	}
	if (*(*tmp)->str)
	{
		(*tmp)->j = 0;
		(*tmp)->str = (*tmp)->str + step;
		((*tmp)->extra != 0) ? ((*tmp)->extra += 1) : (0);
	}
}

inline int kostil_1(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	 if ((g_flags & plus) && (g_flags & minus) && (str[0] == '+'))
	 {
		 ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], str, (*tmp)->n);
		 ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes + 1], symbol, l2);
		 (*tmp)->size_bytes = buff_len + (*tmp)->extra;
		 return (1);
	 }
	return (0);
}

inline int kostil_2(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	if ((g_flags & plus) && (g_flags & minus) && (symbol[0] == '-'))
	{
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], str, (*tmp)->n);
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], symbol, l2);
		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
		return (1);
	}
	return (0);
}

inline int kostil_3(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	if (((g_flags & minus) && (g_flags & zero) && (symbol[0] != '-')))
	{
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], str, (*tmp)->n);
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], symbol, l2);
		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
		return (1);
	}
	return (0);
}

inline int kostil_4(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	if (((g_flags & minus) && (g_flags & zero) && !(g_flags & plus) && (*symbol == '-') ))
	{
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], str, (*tmp)->n);
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], symbol, l2);
		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
		return (1);
	}
	return (0);
}

inline int kostil_5(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	if ((g_flags & minus) && !(g_flags & plus) && !(g_flags & zero) && (*symbol != '-') && (*str != '-') && !(g_flags & space))
	{
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], str, (*tmp)->n);
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], symbol, l2);
		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
		return (1);
	}
	return (0);
}

int kostil_6(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	if ((g_flags & space) && !(g_flags & plus) && (g_flags & minus) && ((*tmp)->j))
	{
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], str, (*tmp)->n);
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes + 1], symbol, l2);
		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
		return (1);
	}
	return (0);
}
int kostil_7(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	if (!(g_flags & plus) && (g_flags & minus) && ((*tmp)->j) && !(g_flags & space))
	{
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], symbol, l2);
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes + l2],str,(*tmp)->n - l2);
		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
		return (1);
	}
	return (0);
}

int kostil_8(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	if ((g_flags & plus) && (g_flags & u || g_flags & U)  && !(g_flags & minus) && !((*tmp)->j) && !(g_flags & space))
	{
		*str += 1;
		ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], symbol, l2);
		(*tmp)->size_bytes = buff_len + (*tmp)->extra;
		return (1);
	}
	return (0);
}

inline int kostili(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	if (kostil_1(tmp,l2,str,symbol))
		return 1;
	if (kostil_2(tmp,l2,str,symbol))
		return 1;
	if (kostil_3(tmp,l2,str,symbol))
		return 1;
	if (kostil_4(tmp,l2,str,symbol))
		return 1;
	if (kostil_5(tmp,l2,str,symbol))
		return 1;
	if (kostil_6(tmp,l2,str,symbol))
		return (1);
	if (kostil_7(tmp,l2,str,symbol))
		return (1);
	if (kostil_8(tmp,l2,str,symbol))
		return (1);
	return (0);
}

inline void pre_output2(t_alist **tmp,size_t l2,char *str, char *symbol)
{
	char str_res[(*tmp)->n + l2 + 1];
	static size_t i;
	
	i = 0;
	if (l2 + (*tmp)->size_bytes > BUFF_SIZE)
	{
		output((*tmp)->fd,(*tmp)->buff,(*tmp)->size_bytes);
		ft_bzero((*tmp)->buff,BUFF_SIZE);
		(*tmp)->i = 0;
		(*tmp)->size_bytes = 0;
		pre_output2(tmp,l2,str,symbol);
		return;
	}
	if (kostili(tmp,l2,str,symbol))
		return ;
	str_res[(*tmp)->n + l2 + 1] = '\0';
	ft_memcpy(&str_res[i], str, (*tmp)->n);
	space_(tmp,&str_res[0],symbol);
	i = (*tmp)->n;
	ft_memcpy(&str_res[i], symbol, l2);
	str_res[(*tmp)->n + l2] = '\0';
	i = 0;
	ft_memcpy(&(*tmp)->buff[(*tmp)->size_bytes], &str_res[i], l2 + (*tmp)->n);
}


inline void pre_output1(t_alist **tmp, size_t *size)
{
	if ((*tmp)->size_bytes == BUFF_SIZE)
	{
		output((*tmp)->fd, (*tmp)->buff,(*tmp)->size_bytes);
		ft_bzero((*tmp)->buff, BUFF_SIZE);
		(*tmp)->i = 0;
	}
	else if (*(*tmp)->str == '%')
	{
		if((*tmp)->j && !(g_flags & minus))
		{
			ft_bchr((const void *) &(*tmp)->buff[(*tmp)->size_bytes], ' ', (*tmp)->size_bytes = (*tmp)->j);
			ft_bchr((const void *) &(*tmp)->buff[(*tmp)->size_bytes - 1], *(*tmp)->str, 1);
			(*tmp)->j = 0;
			*size = 0;
		}
		else if ((*tmp)->j && (g_flags & minus))
		{
			ft_bchr((const void *) &(*tmp)->buff[(*tmp)->size_bytes], ' ', (*tmp)->size_bytes = (*tmp)->j);
			ft_bchr((const void *) &(*tmp)->buff[(*tmp)->size_bytes - (*tmp)->j], *(*tmp)->str, 1);
		}
		else if (!(*tmp)->j && *(*tmp)->str == '%')
			ft_bchr((const void *) &(*tmp)->buff[(*tmp)->size_bytes], *(*tmp)->str, 1);
		(*tmp)->str += 1;
	}
	else
		pre_output3(tmp,size);
}

inline void pre_output3(t_alist **tmp, size_t *size)
{
	if ((*tmp)->j && !(g_flags & minus))
	{
		ft_bchr((const void *) &(*tmp)->buff[(*tmp)->size_bytes], ' ', (*tmp)->size_bytes = (*tmp)->j);
		(*tmp)->j = 0;
		*size = 0;
	}
}

void output(int fd, char *buff, size_t lenght)
{
	if (fd > 0)
		write(fd,&buff[0],lenght);
	if (fd == 0)
		write(1,&buff[0],lenght);
}

//TODO тебе еще не много мучаться - держись



//	char str_res[(*tmp)->n + l2 + 1];
//	static size_t i;
//
//	if (l2 < BUFF_SIZE)
//		return ;
//	str_res[(*tmp)->n + l2 + 1] = '\0';
//	ft_memcpy(&str_res[i],str,(*tmp)->n);
//	i = (*tmp)->n;
//	ft_memcpy(&str_res[i],symbol,l2);
//	str_res[(*tmp)->n + l2] = '\0';
//	i = 0;
//	while (l2 > BUFF_SIZE)
//	{
//			ft_memcpy(&(*tmp)->buff[(*tmp)->i], &str_res[i], BUFF_SIZE);
//			i += BUFF_SIZE;
//			output((*tmp)->fd, (*tmp)->buff, BUFF_SIZE);
//			ft_bzero((*tmp)->buff, BUFF_SIZE);
//			l2 -= BUFF_SIZE;
//			(*tmp)->i = 0;
//	}
//	ft_memcpy(&(*tmp)->buff[(*tmp)->i], &str_res[i],l2);
//	//output((*tmp)->fd, (*tmp)->buff, l2);
//	ft_bzero((*tmp)->buff, BUFF_SIZE);
//	i = 0;

//void b_w(t_alist **tmp,size_t l2,char *str, char *symbol)
//{
//	char fuck[l2 + (*tmp)->n + 1];
//
//	ft_bzero(&fuck[0], l2 + (*tmp)->n);
//	ft_memcpy(&fuck[0],str,(*tmp)->n);
//	ft_memcpy(&fuck[(*tmp)->n],symbol,l2);
//	(*str == '+') ? (1) : (0);
//}

//space_(tmp,l2,&size,&s[0]);
//((g_flags & space) && !(g_flags & plus) && (g_flags & minus) && ((*tmp)->j)) ? (i = (size_t)1) : (0);
//	if (kostil_6(tmp,l2,str,symbol))
//		return ;