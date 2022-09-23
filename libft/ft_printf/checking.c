/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:53:06 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 15:34:56 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_minus_arg(long long arg, t_flags *flag)
{
	if (arg < 0)
	{
		flag->negative = 1;
		flag->space = 0;
	}
	if (arg == 0)
		flag->arg_zero = 1;
}

void	check_minus_arg_f(long double *arg, t_flags *flag)
{
	if (*arg < 0)
	{
		flag->negative = 1;
		flag->space = 0;
		*arg *= -1;
	}
	if (*arg == 0.0)
		flag->arg_zero = 1;
}

void	check_unarg(unsigned long long arg, t_flags *flag)
{
	if (arg == 0)
		flag->arg_zero = 1;
}

void	check_hash_width(t_flags *flag)
{
	if (flag->hash)
	{
		if (flag->specifier == 'o')
			flag->width--;
		if (flag->specifier == 'x' || flag->specifier == 'X' \
			|| flag->specifier == 'p')
			flag->width -= 2;
	}
}
