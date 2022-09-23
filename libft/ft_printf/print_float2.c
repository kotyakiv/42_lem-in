/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:09:43 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 16:22:30 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_arg_f(long double *arg, t_flags *flag, va_list *ap)
{
	if (flag->modifier == 5)
		*arg = va_arg(*ap, long double);
	else
		*arg = (double) va_arg(*ap, double);
}

int	count_dig(char	*part_int, t_flags *flag)
{
	if (flag->precision)
		return (ft_strlen(part_int) + flag->precision);
	else
		return (ft_strlen(part_int));
}

char	*read_int_part(long double *arg)
{
	char		*str;
	long double	temp;
	int			i;
	int			exp;

	exp = 0;
	temp = *arg;
	while (temp >= 10.00)
	{
		temp /= 10;
		++exp;
	}
	str = ft_strnew(exp + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (exp >= 0)
	{
		temp = *arg / ft_pow(10.0, exp);
		str[i] = (int)temp + '0';
		*arg -= ((int)temp * ft_pow(10.0, exp));
		++i;
		exp--;
	}
	return (str);
}

static int	set_prec_f(char **str, t_flags *flag)
{
	if (flag->precision > 310)
	{
		*str = ft_strnew(310);
		return (310);
	}
	*str = ft_strnew(flag->precision + 1);
	return (flag->precision + 1);
}

char	*read_frac_part(long double arg, t_flags *flag)
{
	char		*str;
	char		*temp;
	int			i;
	int			j;

	i = 0;
	j = set_prec_f(&str, flag);
	if (!str)
		return (NULL);
	while (i < j)
	{
		arg *= 10;
		str[i] = (int)arg + '0';
		arg -= ((int)arg);
		++i;
	}
	rounding(&str, 0, flag);
	temp = ft_strsub(str, 0, ft_strlen(str) - 1);
	ft_strdel(&str);
	if (!temp)
		return (NULL);
	str = temp;
	return (str);
}
