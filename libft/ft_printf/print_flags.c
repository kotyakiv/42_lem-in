/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:00:42 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:36:55 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hash(t_flags *flag)
{
	if (flag->hash)
	{
		if (flag->specifier == 'o' || flag->specifier == 'b')
		{
			ft_putchar('0');
			(flag->total)++;
		}
		if (flag->specifier == 'x')
		{
			ft_putstr("0x");
			flag->total += 2;
		}
		if (flag->specifier == 'X')
		{
			ft_putstr("0X");
			flag->total += 2;
		}
	}
}

void	print_sign(t_flags *flag)
{
	if (flag->negative)
	{
		ft_putchar('-');
		(flag->total)++;
	}
	else if (flag->plus)
	{
		ft_putchar('+');
		(flag->total)++;
	}
}

void	print_sign_or_hash(t_flags *flag, int num_dig)
{
	check_hash_width(flag);
	if (flag->precision != -1 || !flag->zero)
	{
		print_width(flag, num_dig, 1);
		if (flag->specifier == 'd' || flag->specifier == 'i' \
			|| flag->specifier == 'f')
			print_sign(flag);
		else if (!flag->arg_zero)
			print_hash(flag);
		else if (flag->specifier == 'o' && !flag->precision && flag->arg_zero)
			print_hash(flag);
	}
	else
	{
		if (flag->specifier == 'd' || flag->specifier == 'i' \
			|| flag->specifier == 'f')
			print_sign(flag);
		else if (!flag->arg_zero)
			print_hash(flag);
		else if (flag->specifier == 'o' && !flag->precision && flag->arg_zero)
			print_hash(flag);
		print_width(flag, num_dig, 1);
	}
}

void	print_flag_space(t_flags *flag)
{
	if (flag->space)
	{
		ft_putchar(' ');
		(flag->total)++;
		if (flag->width)
			flag->width--;
	}
}
