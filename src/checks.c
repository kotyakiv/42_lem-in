/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:17:15 by ykot              #+#    #+#             */
/*   Updated: 2022/10/06 17:02:52 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	check_int(const char *str)
{
	size_t	i;
	size_t	len;

	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	if (len > 11 || (str[0] != '-' && len > 10))
		return (0);
	else if (len == 11 && str[0] == '-')
	{
		str++;
		if (ft_strcmp(str, "2147483648") > 0)
			return (0);
	}
	else if (len == 10 && ft_strcmp(str, "2147483647") > 0)
		return (0);
	i = -1;
	if (str[0] == '-')
		i = 0;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int	is_char_in_str(char c, char *str)
{
	int	i;
	int	found;

	found = FALSE;
	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
		{
			found = TRUE;
			break ;
		}
		i++;
	}
	return (found);
}

int	has_single_dash(char *line)
{
	return (ft_char_count(line, '-') == 1);
}

int	has_double_space(char *line)
{
	return (ft_char_count(line, ' ') == 2);
}

int	check_path_size(int *rooms, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (rooms[i] == 0)
			return (1);
		++i;
	}
	return (0);
}
