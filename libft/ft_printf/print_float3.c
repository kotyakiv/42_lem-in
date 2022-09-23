/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:10:47 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:37:04 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	width_first_call_f(t_flags *flag, int num_dig)
{
	flag->width -= num_dig;
	if (flag->negative || flag->plus)
		flag->width--;
	if (flag->arg_zero && !flag->zero && flag->precision == 0)
		flag->width--;
	if (flag->hash || flag->precision)
		flag->width--;
}

void	print_width_f(t_flags *flag, int num_dig, int first_call)
{
	int	i;

	if (first_call)
		width_first_call_f(flag, num_dig);
	i = 0;
	if (first_call && !flag->minus)
	{
		while (i++ < flag->width)
		{
			if (flag->zero)
			{
				ft_putchar('0');
				(flag->total)++;
			}
			else
				putspace(flag);
		}
	}
	if (!first_call && flag->minus)
	{
		while (i++ < flag->width)
			putspace(flag);
	}
}

void	print_sign_f(t_flags *flag, int num_dig)
{
	if (flag->zero)
	{
		print_sign(flag);
		print_width_f(flag, num_dig, 1);
	}
	else
	{
		print_width_f(flag, num_dig, 1);
		print_sign(flag);
	}
}
