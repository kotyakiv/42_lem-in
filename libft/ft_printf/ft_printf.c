/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:51:09 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:18:11 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_one_char(t_flags *flag, const char *str, int i)
{
	ft_putchar(str[i]);
	flag->total++;
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_flags	flag;
	int		i;

	i = -1;
	ft_bzero(&flag, sizeof(t_flags));
	va_start(ap, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			++i;
			if (!str[i])
				break ;
			if (conv_spec(str, &i, &flag, &ap) || print_conv(&flag, &ap))
			{
				va_end(ap);
				return (-1);
			}
		}
		else
			print_one_char(&flag, str, i);
	}
	va_end(ap);
	return (flag.total);
}
