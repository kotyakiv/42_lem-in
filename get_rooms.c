/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:00:16 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/24 23:23:14 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	is_room_name_valid(char *line)
{
	if (line[0] == 'L')
		return (FALSE);
	return (TRUE);
}

static int is_room_exist(t_farm *farm, char *str)
{
	t_dblist *temp;

	temp = farm->rooms.head;
	while (temp)
	{
		if (ft_strequ(str, ((t_room *)temp->content)->name))
			return (1);
		temp = temp->next;
	}
	return (0);
}

char	**get_room_lines(char **line, t_farm *farm)
{
	char	**str;

	if (ft_strlen(*line) == 0)
		error_free_split_line(farm, NULL, line, "Empty line");
	str = ft_strsplit(*line, ' ');
	if (str == NULL)
		return (NULL);
	if (!is_room_name_valid(str[0]))
		error_free_split_line(farm, NULL, line, "Room begins with L");
	if ((check_int(str[0]) && str[1] == NULL))
		error_free_split_line(farm, NULL, line, "No coordinates or double ant number");
	if (!(check_int(str[1]) && check_int(str[2]) && !str[3]))
	{
		if (str[1] != NULL|| str[2] != NULL)
			error_free_split_line(farm, NULL, line, "Characters after coordinates");
		error_free_split_line(farm, NULL, line, "There are no coordeinates or not integers");
	}
	if (is_room_exist(farm, str[0]))
		error_free_split_line(farm, NULL, line, "Duplicate room");
	return (str);
}

t_list	*lstnew_pointer(void *content)  //where to put this fn, we are using this in checks.c get_rooms.c and hash.c and bfs.c
{
	t_list	*lstnew;

	lstnew = (t_list *)ft_memalloc(sizeof(t_list));
	if (!lstnew)
		return (NULL);
	if (!content)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	else
	{
		lstnew->content = content;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	return (lstnew);
}

t_room	*create_room(char **str)
{
	t_room	*room;

	if (!str)
		return (NULL);
	room = ft_memalloc(sizeof(*room));
	if (!room)
		return (NULL);
	room->name = ft_strdup(str[0]);
	room->coord.x = ft_atoi(str[1]);
	room->coord.y = ft_atoi(str[2]);
	//free_split(&str);
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

t_node	*create_node(char **str, int in_out)  //if 1 in, if 0 out, start or end 2
{
	t_node *node;
	
	if (!str)
		return (NULL);
	node = ft_memalloc(sizeof(*node));
	if (in_out == 1)
		node->name = ft_strjoin(str[0], "_in"); // TO DO: free
	else if (in_out == 0)
		node->name = ft_strjoin(str[0], "_out");
	else
		node->name = ft_strdup(str[0]);
	//free_split(&str);
	return (node);
}
