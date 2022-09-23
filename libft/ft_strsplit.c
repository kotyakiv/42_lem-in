/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:30:06 by ykot              #+#    #+#             */
/*   Updated: 2021/12/15 17:59:22 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_str(char const *str, char c)
{
	size_t	i;
	size_t	n;
	size_t	flag;

	n = 0;
	i = 0;
	flag = 1;
	while (str[i])
	{
		if (str[i] != c && flag)
		{
			flag = 0;
			n++;
		}
		if (str[i] == c && !flag)
		{
			flag = 1;
		}
		i++;
	}
	return (n);
}

static char	*ft_strcut(char const *src, size_t *cnt, char c)
{
	size_t		i;
	size_t		l;
	size_t		j;
	char		*str;

	while (src[*cnt] && src[*cnt] == c)
		(*cnt)++;
	j = *cnt;
	l = 0;
	while (src[*cnt] && src[*cnt] != c)
	{
		l++;
		(*cnt)++;
	}
	str = ft_strnew(l);
	if (!str)
		return (NULL);
	i = 0;
	while (i < *cnt - j)
	{
		str[i] = src[*cnt - l + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	ft_free_split(char ***lines, size_t i)
{
	while (i)
	{
		free((*lines)[i]);
		--i;
	}
	free(*lines);
}

char	**ft_strsplit(char const *s, char c)
{
	size_t		cnt;
	size_t		nb;
	size_t		i;
	char		**lines;

	if (!s)
		return (NULL);
	cnt = 0;
	nb = ft_nb_str(s, c);
	lines = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		lines[i] = ft_strcut(s, &cnt, c);
		if (!lines[i])
		{
			ft_free_split(&lines, i - 1);
			return (NULL);
		}
		++i;
	}
	lines[i] = 0;
	return (lines);
}
