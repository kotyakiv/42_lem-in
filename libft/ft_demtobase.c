/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_demtobase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:45:19 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 14:06:43 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_digit(unsigned long long num, int base)
{
	char	digit;

	if (num % base > 9)
		digit = 'a' + num % base - 10;
	else
		digit = num % base + '0';
	return (digit);
}

char	*ft_demtobase(unsigned long long num, int base)
{
	char	*total;
	int		iter;
	int		i;

	iter = ft_numundig(num, base);
	total = ft_strnew(iter);
	i = 0;
	while (i < iter)
	{
		total[i] = ft_digit(num, base);
		num /= base;
		++i;
	}
	ft_strrev(total);
	return (total);
}
