/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:00:16 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 13:32:38 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	is_room_name_valid(char *line)
{
	if (line[0] == 'L')
		return (FALSE);
	return (TRUE);
}

char	**get_room_lines(char **line, t_farm *farm)
{
	char	**room_lines;

	if (!has_double_space(*line))
		error_free_split_line(farm, NULL, line, ERR_SPACE);
	room_lines = ft_strsplit(*line, ' ');
	if (room_lines == NULL)
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	if (!is_room_name_valid(room_lines[0]))
		error_free_split_line(farm, &room_lines, line, ERR_ROOM_L);
	if ((check_int(room_lines[0]) && room_lines[1] == NULL))
		error_free_split_line(farm, &room_lines, line, ERR_DBL_ANT);
	if (!(check_int(room_lines[1]) && check_int(room_lines[2])))
	{
		if (check_int(room_lines[0]) && room_lines[1] == NULL)
			error_free_split_line(farm, &room_lines, line, ERR_DBL_ANT);
		error_free_split_line(farm, &room_lines, line, ERR_COORD_INT);
	}
	return (room_lines);
}

t_room	*create_room(char **str)
{
	t_room	*room;

	if (!str)
		return (NULL);
	room = (t_room *)ft_memalloc(sizeof(*room));
	if (!room)
		return (NULL);
	room->name = ft_strdup(str[0]);
	if (room->name == NULL)
	{
		free(room);
		return (NULL);
	}
	room->coord.x = ft_atoi(str[1]);
	room->coord.y = ft_atoi(str[2]);
	return (room);
}

int	append_room(t_farm *farm, t_room *room)
{
	t_dblist	*new;

	new = ft_dblstnew_pointer((void *)room);
	if (!new)
		return (0);
	ft_dynlstappend(&farm->rooms, new);
	if (!hashmap_set(farm->hashmap, room->name, room))
		return (0);
	return (1);
}

/*
*	if the node is in, is_in_or_out: 1,
*	if the noode is out, is_in_or_out: 0,
*	if the node is start or end, is_in_or_out: 2
*/

t_node	*create_node(char **str, int is_in_or_out)
{
	t_node	*node;

	if (!str)
		return (NULL);
	node = (t_node *)ft_memalloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	if (is_in_or_out == 1)
		node->name = ft_strjoin(str[0], "_in");
	else if (is_in_or_out == 0)
		node->name = ft_strjoin(str[0], "_out");
	else
		node->name = ft_strdup(str[0]);
	if (node->name == NULL)
	{
		free(node);
		return (NULL);
	}
	return (node);
}
