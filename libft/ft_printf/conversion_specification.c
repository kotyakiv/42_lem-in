/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_specification.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:51:16 by ykot              #+#    #+#             */
/*   Updated: 2022/09/25 15:19:31 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flags_override(t_flags *flag)
{
	if (flag->plus && flag->specifier != 'i' && flag->specifier != 'd' \
		&& flag->specifier != 'f')
		flag->plus = 0;
	if (flag->space && flag->plus)
		flag->space = 0;
	if (flag->minus && flag->zero)
		flag->zero = 0;
	if (flag->precision != -1 && (flag->specifier == 'd' \
		|| flag->specifier == 'i' || flag->specifier == 'x' \
		|| flag->specifier == 'X' || flag->specifier == 'o' \
		|| flag->specifier == 'u'))
		flag->zero = 0;
	if (flag->specifier == 'c' || flag->specifier == 's' || \
		flag->specifier == 'p')
		flag->zero = 0;
	if (flag->specifier == 'f' && flag->precision == -1)
		flag->precision = 6;
}

static void	read_specifier(const char *str, int *i, t_flags *flag)
{
	if (str[*i] == 'd' || str[*i] == 'i' || str[*i] == 'x' || \
		str[*i] == 'X' || str[*i] == 'o' || str[*i] == 'c' || \
		str[*i] == 'p' || str[*i] == 'f' || str[*i] == 's' || \
		str[*i] == 'u' || str[*i] == 'b' || str[*i] == '%')
		flag->specifier = str[*i];
}

static int	max_wid_prec(t_flags *flag)
{
	return (flag->precision > MAX_WP || flag->width > MAX_WP);
}

int	conv_spec(const char *str, int *i, t_flags *flag, va_list *ap)
{
	flag->precision = -1;
	read_flags(str, i, flag);
	if (str[*i] == '*')
		read_star(i, flag, ap, 0);
	else
		read_precision_width(str, i, flag, 0);
	if (str[*i] >= '0' && str[*i] <= '9')
		read_precision_width(str, i, flag, 0);
	if (str[*i] == '.')
	{
		(*i)++;
		if (str[*i] == '*')
			read_star(i, flag, ap, 1);
		else
			read_precision_width(str, i, flag, 1);
		if (str[*i] >= '0' && str[*i] <= '9')
			read_precision_width(str, i, flag, 0);
	}
	read_modifier(str, i, flag);
	read_specifier(str, i, flag);
	flags_override(flag);
	return (max_wid_prec(flag));
}
