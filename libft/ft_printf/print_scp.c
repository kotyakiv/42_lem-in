/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:15:34 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:35:47 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_percent(t_flags *flag)
{
	print_width(flag, 1, 1);
	ft_putchar('%');
	(flag->total)++;
	if (flag->precision == 0)
		flag->width--;
	print_width(flag, 1, 0);
}

void	print_char(t_flags *flag, va_list *ap)
{
	int	arg;

	arg = va_arg(*ap, int);
	print_width(flag, 1, 1);
	ft_putchar(arg);
	(flag->total)++;
	print_width(flag, 1, 0);
}

void	print_pointer(t_flags *flag, va_list *ap)
{
	unsigned long	arg;
	int				num_dig;
	char			*str;

	arg = va_arg(*ap, unsigned long);
	num_dig = ft_numundig(arg, 16);
	if (!arg && flag->precision)
		num_dig = 1;
	flag->width -= 2;
	flag->total += num_dig + 2;
	print_width(flag, num_dig, 1);
	ft_putstr("0x");
	print_precision(flag, num_dig);
	if (!arg && flag->precision)
		ft_putchar('0');
	else
	{
		str = ft_demtobase(arg, 16);
		ft_putstr(str);
		ft_strdel(&str);
	}
	print_width(flag, num_dig, 0);
}

static void	print_str_null(t_flags *flag)
{
	if (flag->precision == -1 || flag->precision >= 6)
	{
		flag->total += 6;
		flag->width -= 6;
		print_width(flag, 0, 1);
		write(1, "(null)", 6);
		print_width(flag, 0, 0);
	}
	else
	{
		flag->width -= flag->precision;
		flag->total += flag->precision;
		print_width(flag, 0, 1);
		write(1, "(null)", flag->precision);
		print_width(flag, 0, 0);
	}
}

void	print_str(t_flags *flag, va_list *ap)
{
	char	*arg;
	int		len;
	int		i;

	arg = va_arg(*ap, char *);
	if (!arg)
	{
		print_str_null(flag);
		return ;
	}
	len = smaller(flag->precision, ft_strlen(arg));
	print_width(flag, len, 1);
	i = 0;
	while (i < len)
	{
		ft_putchar(arg[i++]);
		(flag->total)++;
	}
	print_width(flag, len, 0);
}
