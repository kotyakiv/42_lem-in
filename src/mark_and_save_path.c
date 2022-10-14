/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_and_save_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:07:05 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/09 23:27:16 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset_mark(t_farm *farm)
{
	while (bfs(farm, 2))
	{
		update_fwd_flow(farm, 1);
	}
}

void	set_edge_flow(t_node *the_node, t_dblist *edges,
	t_edge *the_edge, int flow)
{
	while (edges)
	{
		the_edge = edges->content;
		if (the_edge->to == the_node)
		{
			the_edge->flow = flow;
			break ;
		}
		edges = edges->next;
	}
}

static void	init_mark_save_path(t_edge **the_edge, t_dblist **edges,
								t_list **the_path)
{
	*edges = NULL;
	*the_path = NULL;
	*the_edge = NULL;
}

t_list	*mark_and_save_path(t_farm *farm, int flow)
{
	t_node		*the_node;
	t_edge		*the_edge;
	t_dblist	*edges;
	t_list		*the_path;
	t_list		*temp;

	init_mark_save_path(&the_edge, &edges, &the_path);
	the_node = farm->end->in;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges.head;
		set_edge_flow(the_node, edges, the_edge, flow);
		if (the_node->source != farm->start
			&& the_node->source != the_node->parent->source)
		{
			temp = ft_lstnew_pointer(the_node->source->name);
			if (temp == NULL)
				err_nolines(farm, ERR_MEM_ALLOC);
			ft_lstadd(&the_path, temp);
		}
		the_node = the_node->parent;
	}
	return (the_path);
}
