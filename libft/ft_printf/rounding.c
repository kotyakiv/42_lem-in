/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:12:10 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 16:22:55 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	bank_round(long double arg, char *part_int, t_flags *flag)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(part_int);
	arg *= 10;
	if ((int)arg != 5)
		return (1);
	arg -= ((int)arg);
	while (i < 18 - len)
	{
		arg *= 10;
		if ((int)arg != 0)
		{
			flag->int_round = 1;
			return (1);
		}
		arg -= ((int)arg);
		++i;
	}
	if (part_int[len - 1] % 2)
		flag->int_round = 1;
	return (0);
}

int	round_int(char **str, int is_int_part, t_flags *flag, int modflag)
{
	char	*temp;

	if ((*str)[0] == '0' && modflag && is_int_part)
	{
		temp = ft_strjoin("1", *str);
		free(*str);
		if (!temp)
			return (-1);
		*str = temp;
	}
	else if (is_int_part && flag->int_round)
		(*str)[ft_strlen(*str) - 1]++;
	if (modflag && !is_int_part)
		flag->int_round = 1;
	return (0);
}

int	rounding(char **str, int is_int_part, t_flags *flag)
{
	int	i;
	int	modflag;

	modflag = 1;
	i = ft_strlen(*str) - 1;
	if (!is_int_part)
		(*str)[i] += 4;
	while (modflag && i >= 0)
	{
		modflag = 0;
		(*str)[i]++;
		if ((*str)[i] > '9')
		{
			(*str)[i] = '0';
			modflag = 1;
			--i;
		}
		else if (flag->int_round && is_int_part)
			flag->int_round = 0;
	}
	if (round_int(str, is_int_part, flag, modflag) == -1)
		return (-1);
	return (0);
}
