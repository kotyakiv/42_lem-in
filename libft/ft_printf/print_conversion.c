/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:02:32 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:37:29 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_conv(int select, t_flags *flag, va_list *ap)
{
	t_conversion	*table[9];

	table[0] = print_char;
	table[1] = print_str;
	table[2] = print_pointer;
	table[3] = print_decimal;
	table[4] = print_octal;
	table[5] = print_hexadecimal;
	table[6] = print_unsigned;
	table[7] = print_float;
	table[8] = print_binary;
	table[select](flag, ap);
}

int	print_conv(t_flags *flag, va_list *ap)
{
	if (flag->specifier == '%')
		print_percent(flag);
	if (flag->specifier == 'c')
		type_conv(0, flag, ap);
	if (flag->specifier == 's')
		type_conv(1, flag, ap);
	if (flag->specifier == 'p')
		type_conv(2, flag, ap);
	if (flag->specifier == 'd' || flag->specifier == 'i')
		type_conv(3, flag, ap);
	if (flag->specifier == 'o')
		type_conv(4, flag, ap);
	if (flag->specifier == 'x' || flag->specifier == 'X')
		type_conv(5, flag, ap);
	if (flag->specifier == 'u')
		type_conv(6, flag, ap);
	if (flag->specifier == 'f')
		type_conv(7, flag, ap);
	if (flag->specifier == 'b')
		type_conv(8, flag, ap);
	return (flag->total == -1);
}
