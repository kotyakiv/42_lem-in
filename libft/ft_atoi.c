/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 17:58:58 by ykot              #+#    #+#             */
/*   Updated: 2021/11/23 14:29:05 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_whitespaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

static int	ft_atoi_sign(const char *str, size_t i, int *minus)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*minus = -1;
		return (1);
	}
	return (0);
}

static int	ft_max_long_border(const char *s, size_t i, int m, size_t iter)
{
	if (iter > 18 || (iter == 17 && (s[i] != '0' \
		|| (m == 1 && s[i] == '0' && (s[i + 1] == '8' || s[i + 1] == '9')) \
		|| (m == -1 && s[i] == '0' && (s[i + 1] == '9')))))
	{
		if (m == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		total;
	int		minus;
	size_t	iter;
	size_t	i;

	iter = 0;
	minus = 1;
	total = 0;
	i = 0;
	while (ft_whitespaces(str[i]))
		++i;
	if (ft_atoi_sign(str, i, &minus))
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ft_max_long_border(str, i, minus, iter) == 1)
			return (-1);
		if (ft_max_long_border(str, i, minus, iter) == -1)
			return (0);
		total *= 10;
		total += str[i] - '0';
		++i;
		++iter;
	}
	return (total * minus);
}
