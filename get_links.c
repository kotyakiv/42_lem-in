/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:50:17 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/24 18:14:00 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	append_edge(t_node *node, t_edge *edge)  // rooms will be changed to nodes here
{
	t_dblist	*new;

	new = ft_dblstnew_pointer(edge);
	if (!new)
		return (0); //TO DO: error exit 
	ft_dynlstappend(&node->edges, new);
	return (1);
}

/*
	1_in --> 1_out --> 2_in --> 2_out
	 ^							  |
	 |							  |
	  -----------------------------
*/
static int	make_adj_list(t_room *room1, t_room *room2) // modify this to put room_in room_out links
{
	t_edge *edge1_in;
	t_edge *edge2_in;

	edge1_in = NULL;
	edge2_in = NULL;
	if (room1->out && room2->in)
	{
		edge2_in = create_edge(room2->in);
		if (!append_edge(room1->out, edge2_in))
			return (FALSE);
	}
	if (room2->out && room1->in)
	{
		edge1_in = create_edge(room1->in);
		if (!append_edge(room2->out, edge1_in))
			return (FALSE);
	}
	return (TRUE);
}

void parse_links(t_farm *farm, char *line)
{
	char	*first;
	char	*second;
	t_room	*room1;
	t_room	*room2;
	char **split_link;

	split_link = ft_strsplit(line, '-');
	if (split_link[0] && split_link[1] && split_link[2])
		error_free_split_line(farm, &split_link, &line, "Wrong link");
	if (!split_link[0] || !split_link[1] || split_link[2])
		error_free_split_line(farm, &split_link, &line, "Memory allocation");
	first = split_link[0];
	second = split_link[1];
	if (ft_strequ(first, second))
		error_free_split_line(farm, &split_link, &line, "Same room in the link");
	room1 = (t_room *)hashmap_get(farm->hashmap, first);
	room2 = (t_room *)hashmap_get(farm->hashmap, second);
	if (!room1 || !room2)
		error_free_split_line(farm, &split_link, &line, "Wrong link");
	if (!make_adj_list(room1, room2))
		error_free_split_line(farm, &split_link, &line, "Memory allocation");
	free_split(&split_link);
}

int	get_link(t_farm *farm, char **line)
{
	parse_links(farm, *line);  //adj_list is created here now
	return (1);
}

t_edge *create_edge(t_node *node)
{
	t_edge *edge;

	if (!node)
		return (NULL);
	edge = (t_edge *)ft_memalloc(sizeof(t_edge));
	if (!edge)
		return (NULL); // to do error exit
	edge->to = node;
	return (edge);
}
