/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:30:30 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:36:20 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	if_not_nan_inf(long double arg, t_flags *flag, char **part_int)
{
	if (arg != arg)
	{
		*part_int = ft_strdup("nan");
		flag->zero = 0;
		flag->precision = 0;
		return (0);
	}
	if (arg == 1.0 / 0.0)
	{
		*part_int = ft_strdup("inf");
		flag->precision = 0;
		flag->zero = 0;
		return (0);
	}
	if (arg == -1.0 / 0.0)
	{
		*part_int = ft_strdup("-inf");
		flag->precision = 0;
		flag->zero = 0;
		return (0);
	}
	return (1);
}

static int	read_int_fr(long double arg, t_flags *flag, \
						char **p_int, char **p_fr)
{
	check_minus_arg_f(&arg, flag);
	*p_int = read_int_part(&arg);
	if (!p_int)
		return (-1);
	if (flag->precision == 0)
	{
		if (bank_round(arg, *p_int, flag))
		{
			*p_fr = read_frac_part(arg, flag);
			if (!p_fr)
				return (-1);
		}
	}
	else
	{
		*p_fr = read_frac_part(arg, flag);
		if (!p_fr)
			return (-1);
	}
	if (flag->int_round)
		if (rounding(p_int, 1, flag) == -1)
			return (-1);
	return (0);
}

static void	free_all_str(char *part_int, char *part_frac)
{
	ft_strdel(&part_int);
	ft_strdel(&part_frac);
}

static void	print_prec_f(char *part_frac, t_flags *flag)
{
	int	i;

	if (flag->hash || flag->precision)
	{
		ft_putchar('.');
		(flag->total)++;
	}
	if (flag->precision)
	{
		if (flag->precision <= 310)
			ft_putstr(part_frac);
		else
		{
			ft_putstr(part_frac);
			i = flag->precision - 310 + 1;
			while (i)
			{
				ft_putchar('0');
				--i;
			}
		}
	}
}

void	print_float(t_flags *flag, va_list *ap)
{
	long double	arg;
	char		*part_int;
	char		*part_frac;
	int			num_dig;

	part_int = NULL;
	part_frac = NULL;
	read_arg_f(&arg, flag, ap);
	if (if_not_nan_inf(arg, flag, &part_int))
	{
		if (read_int_fr(arg, flag, &part_int, &part_frac) == -1)
		{
			free_all_str(part_int, part_frac);
			flag->total = -1;
			return ;
		}
	}
	num_dig = count_dig(part_int, flag);
	print_flag_space(flag);
	print_sign_f(flag, num_dig);
	ft_putstr(part_int);
	print_prec_f(part_frac, flag);
	print_width_f(flag, num_dig, 0);
	flag->total += num_dig;
	free_all_str(part_int, part_frac);
}
