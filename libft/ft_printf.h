/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 21:58:52 by ablizniu          #+#    #+#             */
/*   Updated: 2018/05/06 22:29:44 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>
#include <wchar.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <locale.h>

/*----------------------------------MAP-------------------------------------*/
/*00000000|0000000S|SF000000|00000000|  - var at start						*/
/*3 specification 4|2       |1  flags| end - global var						*/
/*--------------------------------------------------------------------------*/

#define first       0
#define second      0xC080
#define third       0xE08080
#define fourth      0xF0808080
#define buff_len  ft_strlen((*tmp)->buff)

typedef enum flags
{
	hash =	0x1,
	zero =	0x2,
	plus =	0x4,
	minus =	0x8,
	space = 0x10,
	presicions = 0x20,
	n = 0x40,
	ptr = 0x80,
	/*--------- first byte--------*/
	dollar = 0x100,
	hh	=	0x200,
	h	=	0x400,
	l	=	0x800,
	ll	=	0x1000,
	j	= 	0x2000,
	z	= 	0x4000,
	C = 0x8000,
	/*----------second_byte_______*/
	d = 0x10000,
	i = 0x20000,
	s = 0x40000,
	o = 0x80000,
	p = 0x100000,
	x = 0x200000,
	c = 0x400000,
	u = 0x800000,
	/*-----------third_byte--------*/
	D = 0x1000000,
	S = 0x2000000,
	O = 0x4000000,
	U = 0x8000000,
	X = 0x10000000,
	b = 0x20000000,
	B = 0x40000000,
	k = 0x80000000,
	/*-----------fourth_byte------*/
} flags;

flags f_a;
unsigned int g_flags;

int ft_printf(const char *format,...);
int ft_fpritnf(const int fd,const char *format,...);
int ft_printf_core(va_list ag, t_alist *tmp);
int validator_specificators_and_flags(va_list ap, t_alist **tmp);

uintmax_t isflags_unsigned(va_list ap);
intmax_t isflags_signed(va_list ap);

int isflag(void);
int search(void);

void validator_flags(t_alist **tmp);
int validator_flags_2(t_alist **tmp);

void buffering(t_alist **tmp,int step, size_t size, char *symbol);

int fill_bits(t_alist **tmp);
void fill_bits_a(t_alist **tmp);
int ft_printf_processing(va_list ap, t_alist **tmp);

void d_i(t_alist **tmp, va_list ap);
void d_D_i_presisions(t_alist **tmp, size_t l, char *str, int *res);
int zero_decimal_integer(t_alist **tmp, intmax_t n);

void u_u(t_alist **tmp, va_list ap);
void u_U_presisions(t_alist **tmp, size_t l, char *str, int *res);
void o_t(t_alist **tmp, va_list ap);
void x_hex(t_alist **tmp, va_list ap);
void b_binary(t_alist **tmp, va_list ap);
void p_pointer_addres(t_alist **tmp, va_list ap);
void k_time_date(t_alist **tmp, va_list ap);
void c_character(t_alist **tmp, va_list ap);
void c_EOF(t_alist **tmp);
void format_len(t_alist **tmp);
//void pres_c_EOF(t_alist **tmp);
int width_c_EOF(t_alist **tmp);
void p_b_f(t_alist **tmp,int step, size_t size);
void s_string(t_alist **tmp, va_list ap);
void unicode_C(t_alist **tmp, va_list ap);
void unicode_S(t_alist **tmp, va_list ap);
void unicode_0(t_alist **tmp, unsigned int value);
void unicode_1(t_alist **tmp, unsigned int value);
void unicode_2(t_alist **tmp, unsigned int value);
void unicode_3(t_alist **tmp, unsigned int value);

// hash сделан
int hash_(t_alist **tmp,size_t l, char *str);
void width(t_alist **tmp);
int presic_(t_alist **tmp);
void space_(t_alist **tmp, char *str, char *symbol);
int hash_and_presic_x_X(t_alist **tmp,size_t l, char *str);
int hash_and_presic_o_O(t_alist **tmp,size_t l, char *str);
int x_X_zero_width(t_alist **tmp,size_t l, char *str);
int x_X_precision(t_alist **tmp,size_t l, char *str, int *res);
int o_O_precision(t_alist **tmp,size_t l, char *str, int *res);
int S_s_precision(t_alist **tmp,size_t l, char *str);


int kostili(t_alist **tmp,size_t l2,char *str, char *symbol);
int kostil_1(t_alist **tmp,size_t l2,char *str, char *symbol);
int kostil_2(t_alist **tmp,size_t l2,char *str, char *symbol);
int kostil_3(t_alist **tmp,size_t l2,char *str, char *symbol);
int kostil_4(t_alist **tmp,size_t l2,char *str, char *symbol);
int kostil_5(t_alist **tmp,size_t l2,char *str, char *symbol);
int kostil_6(t_alist **tmp,size_t l2,char *str, char *symbol);
int kostil_7(t_alist **tmp,size_t l2,char *str, char *symbol);
int kostil_8(t_alist **tmp,size_t l2,char *str, char *symbol);

int kostil_space(t_alist **tmp, char **symbol, size_t *size, char *str);

void b_w(t_alist **tmp,size_t l2,char *str, char *symbol);
void p_m(t_alist **tmp, char **symbol, size_t *size, char *str);
void w_m(t_alist **tmp, size_t *size, char **symbol, char *str);
void min_(t_alist **tmp, char **symbol, size_t *size, char *str);
void plus_(t_alist **tmp, char **symbol, char *str);

void output(int fd, char *buff, size_t lenght);
void pre_output1(t_alist **tmp,size_t *size);
void pre_output2(t_alist **tmp,size_t l2,char *str, char *symbol);
void pre_output3(t_alist **tmp, size_t *size);
void ft_itoa_base_printf_u(uintmax_t num, int base, int up,t_alist **tmp);
void ft_itoa_base_printf_s(intmax_t n, int base, int up,t_alist **tmp);
#endif