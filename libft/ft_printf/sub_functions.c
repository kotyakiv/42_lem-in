/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:47:22 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 16:22:59 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putllunbr(unsigned long long n)
{
	char	c;

	if (n >= 10)
		putllunbr(n / 10);
	c = n % 10 + '0';
	ft_putchar(c);
}

long long	smaller(long long a, long long b)
{
	if (a < b && a >= 0)
		return (a);
	else
		return (b);
}
