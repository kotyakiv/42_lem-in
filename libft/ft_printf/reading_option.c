/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:06:54 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 16:22:50 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_flags(const char *str, int *i, t_flags *flag)
{
	while (str[*i] == '-' || str[*i] == '+' || str[*i] == '#' \
	|| str[*i] == '0' || str[*i] == ' ' || str[*i] == '\'')
	{
		if (str[*i] == '-')
			flag->minus = 1;
		if (str[*i] == '+')
			flag->plus = 1;
		if (str[*i] == '#')
			flag->hash = 1;
		if (str[*i] == '0')
			flag->zero = 1;
		if (str[*i] == ' ')
			flag->space = 1;
		(*i)++;
	}
}

void	read_precision_width(const char *str, int *i, t_flags *flag, int is_pr)
{
	char	*char_number;
	int		j;

	char_number = ft_strnew(11);
	while (str[*i] == '0')
	{
		if (is_pr)
			flag->precision = 0;
		(*i)++;
	}
	j = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		char_number[j++] = str[*i];
		(*i)++;
	}
	if (is_pr)
		flag->precision = ft_atoi(char_number);
	else
		flag->width = ft_atoi(char_number);
	ft_strdel(&char_number);
}

static void	read_dl_mod(const char *str, int *i, t_flags *flag)
{
	if (str[*i] == 'L')
	{
		flag->modifier = 5;
		(*i)++;
	}
}

void	read_modifier(const char *str, int *i, t_flags *flag)
{
	if (str[*i] == 'h')
	{
		if (str[*i + 1] == 'h')
		{
			flag->modifier = 1;
			(*i)++;
		}
		else
			flag->modifier = 2;
		(*i)++;
	}
	if (str[*i] == 'l')
	{
		if (str[*i + 1] == 'l')
		{
			flag->modifier = 4;
			(*i)++;
		}
		else
			flag->modifier = 3;
		(*i)++;
	}
	read_dl_mod(str, i, flag);
}

void	read_star(int *i, t_flags *flag, va_list *ap, int is_prec)
{
	if (!is_prec)
		flag->width = va_arg(*ap, int);
	else
		flag->precision = va_arg(*ap, int);
	if (!is_prec && flag->width < 0)
	{
		flag->width *= -1;
		flag->minus = 1;
	}
	else if (is_prec && flag->precision < 0)
		flag->precision = -1;
	(*i)++;
}
