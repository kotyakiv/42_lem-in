/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:50:20 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:37:21 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	read_signedarg(long long *arg, t_flags *flag, va_list *ap)
{
	if (flag->modifier == 1)
		*arg = (char) va_arg(*ap, int);
	else if (flag->modifier == 2)
		*arg = (short) va_arg(*ap, int);
	else if (flag->modifier == 3)
		*arg = (long) va_arg(*ap, long long);
	else if (flag->modifier == 4)
		*arg = va_arg(*ap, long long);
	else
		*arg = (int) va_arg(*ap, int);
}

void	print_decimal(t_flags *flag, va_list *ap)
{
	long long	arg;
	int			num_dig;

	read_signedarg(&arg, flag, ap);
	num_dig = ft_numdig(arg, 10);
	check_minus_arg(arg, flag);
	print_flag_space(flag);
	print_sign_or_hash(flag, num_dig);
	print_precision(flag, num_dig);
	if (arg)
	{
		ft_putllnbr(arg);
		flag->total += num_dig;
	}
	else if (!flag->zero_printed && flag->precision)
	{
		ft_putchar('0');
		(flag->total)++;
	}
	print_width(flag, num_dig, 0);
}
