/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:25:04 by ykot              #+#    #+#             */
/*   Updated: 2022/07/14 15:56:04 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/**
 * If input is incorrect free previous allocated memmory
**/

static int	free_split(char ***str)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
		ft_strdel(str[i++]);
	ft_strdel(**str);
	return (1);
}

/**
 * Read and check all arguments
**/
/*
static int	read_rooms(t_list **rooms, const char *argv)
{
	char	**str;
	int		num;
	int		*numptr;
	t_list	*temp;
	size_t	i;

	numptr = &num;
	i = -1;
	str = ft_strsplit(argv, ' ');
	if (!str)
		return (1);
	while (str[++i])
	{
		if (check_int(str[i]))
			return (free_split(&str));
		num = ft_atoi(str[i]);

		temp = ft_lstnew(numptr, sizeof(int));
		if (!temp)
			return (free_split(&str));
		ft_lstappend(&(*a), temp);
	}
	//free_split(&str);
	return (0);
}
*/

static int	read_rooms(t_list **rooms, const char *argv)
{
	char	**str;
	t_node	room;
	t_node	*roomptr;
	
}

void	read_arg(int argc, char **argv, t_list **rooms, int num_ants)
{
	char	*line;
	int		i;

	i = 1;
	while (i < argc)
	{
		if (get_next_line(0, &line))
			error(rooms);
	}
}


int	read_arg(char **argv, t_list **rooms, int num_ants)
{
	size_t	i;
	int		startmod;
	int		endmod;

	startmod = 0;
	endmod = 0;
	i = 1;
	if (check_int(argv[i++]))
		error(rooms);
	if()
}

