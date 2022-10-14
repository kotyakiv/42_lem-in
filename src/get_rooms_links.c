/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:33:40 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 12:00:52 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	set_nodes(char **room_lines, t_room *room)
{
	t_edge	*edge;

	room->in = create_node(room_lines, 1);
	room->out = create_node(room_lines, 0);
	if (room->in == NULL || room->out == NULL)
	{
		del_rooms(room);
		return (0);
	}
	room->in->source = room;
	room->out->source = room;
	edge = create_edge(room->out);
	if (edge == NULL)
	{
		del_rooms(room);
		return (0);
	}
	if (append_edge(room->in, edge) == 0)
	{
		free(edge);
		return (0);
	}
	return (1);
}

static int	get_rooms(t_farm *farm, char *line)
{
	char	**room_lines;
	t_room	*room;

	if (!farm->flag.rooms_done && has_double_space(line))
	{
		room_lines = get_room_lines(&line, farm);
		if (room_lines == NULL)
			error_free_split_line(farm, NULL, &line, ERR_MEM_ALLOC);
		if (is_in(farm->hashmap, room_lines[0]))
			error_free_split_line(farm, &room_lines, &line, ERR_DBL_ROOM);
		room = create_room(room_lines);
		if (room == NULL)
			error_free_split_line(farm, NULL, &line, ERR_MEM_ALLOC);
		if (set_nodes(room_lines, room) == 0)
			error_free_split_line(farm, NULL, &line, ERR_MEM_ALLOC);
		if (append_room(farm, room) == 0)
			error_free_split_line(farm, NULL, &line, ERR_MEM_ALLOC);
		free_split(&room_lines);
		return (1);
	}
	return (0);
}

static int	get_links(t_farm *farm, char *line)
{
	char	**room_lines;

	if (is_char_in_str('-', line))
	{
		farm->flag.rooms_done = 1;
		if (farm->rooms.head == NULL)
			error_free_split_line(farm, NULL, &line, ERR_ROOM);
		if (get_link(farm, &line))
		{
			farm->flag.is_links = 1;
			return (1);
		}
	}
	room_lines = get_room_lines(&line, farm);
	if (farm->flag.rooms_done == 1 && room_lines)
		error_free_split_line(farm, &room_lines, &line, ERR_ROOM_AFT_LINK);
	return (0);
}

int	get_rooms_links(t_farm *farm, char *line)
{
	if (get_rooms(farm, line))
		return (1);
	if (get_links(farm, line))
		return (1);
	return (0);
}
