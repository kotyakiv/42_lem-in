/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_residual_flow.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:15:37 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/23 18:19:54 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	create_rev_flow(t_node *the_node, t_dblist *edges,
	t_edge *the_edge, t_farm *farm)
{
	while (edges)
	{
		the_edge = edges->content;
		if (the_edge->to == the_node)
		{
			the_edge->flow = 1;
			if (!the_edge->reverse)
			{
				the_edge->reverse = create_edge(the_node->parent);
				if (!append_edge(the_node, the_edge->reverse))
					error(farm, "Memory allocation");
				the_edge->reverse->reverse = the_edge;
			}
			break ;
		}
		edges = edges->next;
	}
}

void	update_res_flow(t_farm *farm)
{
	t_node		*the_node;
	t_edge		*the_edge;
	t_dblist	*edges;

	the_node = farm->end->in;
	edges = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges.head;
		create_rev_flow(the_node, edges, the_edge, farm);
		the_node = the_node->parent;
	}
}
