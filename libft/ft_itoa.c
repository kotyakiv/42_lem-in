/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:31 by ykot              #+#    #+#             */
/*   Updated: 2021/11/23 14:38:40 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_put_in_str(char **str, int minus, int n, int len)
{
	if (minus)
	{
		while (len > 0)
		{
			(*str)[len--] = n % 10 + '0';
			n /= 10;
		}
		(*str)[0] = '-';
	}
	else
	{
		while (len >= 0)
		{
			(*str)[len--] = n % 10 + '0';
			n /= 10;
		}
	}
}

static size_t	ft_itoa_count_len(int *minus, int n)
{
	int	len;

	len = 0;
	*minus = 0;
	if (n < 0)
	{
		++len;
		*minus = 1;
		n *= -1;
	}
	while (n > 9)
	{
		++len;
		n /= 10;
	}
	return (++len);
}

char	*ft_itoa(int n)
{
	char	*newstr;
	size_t	len;
	int		minus;

	if (n == -2147483648)
	{
		newstr = ft_strdup("-2147483648");
		return (newstr);
	}
	else if (n == 0)
	{
		newstr = ft_strdup("0");
		return (newstr);
	}
	len = ft_itoa_count_len(&minus, n);
	newstr = ft_strnew(len);
	if (!newstr)
		return (NULL);
	if (minus)
		n *= -1;
	ft_itoa_put_in_str(&newstr, minus, n, len - 1);
	return (newstr);
}
