/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:48:28 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:20:13 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_unsignedarg(unsigned long long *arg, t_flags *flag, va_list *ap)
{
	if (flag->modifier == 1)
		*arg = (unsigned char) va_arg(*ap, unsigned int);
	else if (flag->modifier == 2)
		*arg = (unsigned short) va_arg(*ap, unsigned int);
	else if (flag->modifier == 3)
		*arg = (unsigned long) va_arg(*ap, unsigned long long);
	else if (flag->modifier == 4)
		*arg = va_arg(*ap, unsigned long long);
	else
		*arg = (unsigned int) va_arg(*ap, unsigned int);
}

void	print_unsigned(t_flags *flag, va_list *ap)
{
	unsigned long long	arg;
	int					num_dig;

	read_unsignedarg(&arg, flag, ap);
	num_dig = ft_numundig(arg, 10);
	check_unarg(arg, flag);
	print_sign_or_hash(flag, num_dig);
	print_precision(flag, num_dig);
	if (arg)
	{
		putllunbr(arg);
		flag->total += num_dig;
	}
	else if (!flag->zero_printed && flag->precision)
	{
		ft_putchar('0');
		(flag->total)++;
	}
	print_width(flag, num_dig, 0);
}

void	print_octal(t_flags *flag, va_list *ap)
{
	unsigned long long	arg;
	int					num_dig;
	char				*str;

	read_unsignedarg(&arg, flag, ap);
	num_dig = ft_numundig(arg, 8);
	check_unarg(arg, flag);
	print_sign_or_hash(flag, num_dig);
	print_precision(flag, num_dig);
	if (arg)
	{
		str = ft_demtobase(arg, 8);
		ft_putstr(str);
		ft_strdel(&str);
		flag->total += num_dig;
	}
	else if (!flag->zero_printed && flag->precision)
	{
		ft_putchar('0');
		(flag->total)++;
	}
	print_width(flag, num_dig, 0);
}

void	print_binary(t_flags *flag, va_list	*ap)
{
	unsigned long long	arg;
	int					num_dig;
	char				*str;

	read_unsignedarg(&arg, flag, ap);
	num_dig = ft_numundig(arg, 2);
	check_unarg(arg, flag);
	print_sign_or_hash(flag, num_dig);
	print_precision(flag, num_dig);
	if (arg)
	{
		str = ft_demtobase(arg, 2);
		ft_putstr(str);
		ft_strdel(&str);
		flag->total += num_dig;
	}
	else if (!flag->zero_printed && flag->precision)
	{
		ft_putchar('0');
		(flag->total)++;
	}
	print_width(flag, num_dig, 0);
}

void	print_hexadecimal(t_flags *flag, va_list *ap)
{
	unsigned long long	arg;
	int					num_dig;
	char				*str;

	read_unsignedarg(&arg, flag, ap);
	num_dig = ft_numundig(arg, 16);
	check_unarg(arg, flag);
	print_sign_or_hash(flag, num_dig);
	print_precision(flag, num_dig);
	if (arg)
	{
		str = ft_demtobase(arg, 16);
		if (flag->specifier == 'X')
			ft_strtoup(str);
		ft_putstr(str);
		ft_strdel(&str);
		flag->total += num_dig;
	}
	else if (!flag->zero_printed && flag->precision)
	{
		ft_putchar('0');
		(flag->total)++;
	}
	print_width(flag, num_dig, 0);
}
