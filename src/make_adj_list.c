/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_adj_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:42:01 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/09 23:31:12 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge	*create_edge(t_node *node)
{
	t_edge	*edge;

	if (!node)
		return (NULL);
	edge = (t_edge *)ft_memalloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->to = node;
	edge->flow = 0;
	return (edge);
}

int	append_edge(t_node *node, t_edge *edge)
{
	t_dblist	*new;

	if (!node || !edge)
		return (0);
	new = ft_dblstnew_pointer(edge);
	if (!new)
		return (0);
	ft_dynlstappend(&node->edges, new);
	return (1);
}

int	make_adj_list(t_room *room1, t_room *room2)
{
	t_edge	*edge1_in;
	t_edge	*edge2_in;

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
