/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:54:35 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 14:07:47 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* Sets the given option for the bfs_path funciton */
static int	set_option(int option, t_list **visited,
	t_edge *the_edge, t_node *child)
{
	if (option == 1)
		return (!is_in(visited, child->name)
			&& the_edge->flow == 1
			&& the_edge->reverse && the_edge->reverse->flow == 0);
	if (option == 2)
		return (!is_in(visited, child->name)
			&& ((the_edge->flow == 1
					&& the_edge->reverse && the_edge->reverse->flow == 0)
				|| (the_edge->flow == 0 && !the_edge->reverse)));
	return (0);
}

/* 
	Iterate through edges. If the child node is not visited, 
	set the given option for bfs_path,
	set its parent and add the child to the queue.
*/
static int	find_edge_set_opt(t_node *the_node, int option,
	t_list **queue, t_list **visited)
{
	t_dblist	*edges;
	t_edge		*the_edge;
	t_node		*child;

	edges = the_node->edges.head;
	while (edges)
	{
		the_edge = edges->content;
		child = the_edge->to;
		if (set_option(option, visited, the_edge, child))
		{
			child->parent = the_node;
			if (q_push(queue, child) == 0)
				return (0);
		}
		edges = edges->next;
	}
	return (1);
}

/*
	This function finds the shortest node-disjoint path 
	and sets parent nodes for that path
	Option 1: Edge flow is 1 and there is reverse edge 
			(only the edges found by Edmonds-Karp algo)
	Option 2: Edge flow is 1 and there is reverse edge OR
			Edge flow is 0 and no reverse edge
*/
int	bfs_path(t_farm *farm, int option)
{
	t_node	*the_node;
	t_list	*queue;
	t_list	**visited;

	visited = (t_list **)ft_memalloc(HASH * sizeof(t_list *));
	if (visited == NULL)
		err_nolines(farm, ERR_MEM_ALLOC);
	queue = NULL;
	if (q_push(&queue, farm->start->out) == 0)
		free_err_hashmap(farm, &queue, visited);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
			return (free_and_exit_bfs(&queue, visited, 1));
		if (hashmap_set(visited, the_node->name, the_node) == 0)
			free_err_hashmap(farm, &queue, visited);
		if (find_edge_set_opt(the_node, option, &queue, visited) == 0)
			free_err_hashmap(farm, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 0));
}
