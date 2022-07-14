/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:20:47 by ykot              #+#    #+#             */
/*   Updated: 2022/07/14 16:08:44 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM-IN_H
# define LEM-IN_H
# include "libft.h"

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct	s_room
{
	char	*name;
	int		occupied;
	t_coord	coord;
}				t_room;

typedef struct	s_farm
{
	int		num_ants;
	t_list	*rooms;
	t_list	*links;
}				t_farm;

void	read_arg(int argc, char **argv, t_farm *map);
void	error(t_list **rooms);
int		check_int(const char *str);

#endif
