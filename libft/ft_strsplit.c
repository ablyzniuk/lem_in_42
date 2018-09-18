/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <ablizniu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:56:15 by ablizniu          #+#    #+#             */
/*   Updated: 2017/11/29 19:54:06 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int		i;
	int		n;
	char	*str;

	n = 0;
	i = 0;
	str = (char *)s;
	if (!s || !c)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == c)
		{
			if (str[i + 1] == '\0')
				return (n);
			i++;
		}
		n++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (n);
}

static char	*cut_dilims(const char *s, size_t *k, char c)
{
	size_t	i;
	char	*str;
	char	*buff;

	str = (char *)s;
	while (str[*k] == c)
		*k += 1;
	i = *k;
	while (str[*k])
	{
		if (str[*k] == c)
			break ;
		*k += 1;
	}
	buff = ft_strsub(str, (unsigned int)i, *k - i);
	return (buff);
}

char		**ft_strsplit(const char *s, char c)
{
	int		i;
	size_t	k;
	int		n;
	char	*buff;
	char	**str_s;

	i = 0;
	k = 0;
	n = word_count(s, c);
	str_s = (char **)malloc(sizeof(char *) * (n + 1));
	if (str_s == NULL)
		return (NULL);
	while (i < n)
	{
		buff = cut_dilims((char *)s, &k, c);
		str_s[i] = ft_strdup(buff);
		ft_strdel(&buff);
		i++;
	}
	str_s[i] = NULL;
	return (str_s);
}
