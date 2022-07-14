/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:17:15 by ykot              #+#    #+#             */
/*   Updated: 2022/07/14 15:19:39 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	check_int(const char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	if (len > 11 || (str[0] != '-' && len > 10))
		return (1);
	else if (len == 11 && str[0] == '-')
	{
		str++;
		if (ft_strcmp(str, "2147483648") > 0)
			return (1);
	}
	else if (len == 10 && ft_strcmp(str, "2147483647") > 0)
		return (1);
	i = 0;
	if (str[0] == '-')
		i = 1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		++i;
	}
	return (0);
}
