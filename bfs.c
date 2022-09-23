/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/21 11:01:31 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

static void null_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void q_push(t_list **queue, t_node *the_node)
{
	t_list *to_push;
	to_push = lstnew_pointer(the_node);
	if (!to_push)
		return ;
	ft_lstappend(queue, to_push);
}

t_node *q_pop(t_list **queue)
{
	t_node *the_node;

	if (!queue)
		return (NULL);
	the_node = (*queue)->content;
	ft_lstdelelem(queue, 0, null_fn);
	return (the_node);
}

static int	free_and_exit_bfs(t_list **queue, t_list **visited, int exit)
{
	ft_lstdel(queue, null_fn);
	free_hashmap(visited);
	return (exit);
}

static void find_edge(t_node *the_node, int flow, t_list **queue, t_list **visited)
{
	t_dblist	*edges;
	t_edge	*the_edge;
	t_node	*child;

	edges = the_node->edges.head;
	while (edges)
	{
		the_edge = edges->content;
		child = the_edge->to;
		if (the_edge->flow == flow && !is_in(visited, child->name))
		{
			child->parent = the_node;
			q_push (queue, child);
		}
		edges = edges->next;
	}
}

int bfs(t_farm *farm, int flow)  // if it reaches to end return 1, else 0
{
	t_node	*the_node;
	t_list	*queue;
	t_list	**visited;

	visited = ft_memalloc(HASH * sizeof(t_list *));
	queue = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
			return (free_and_exit_bfs(&queue, visited, 1));
		hashmap_set(visited, the_node->name, the_node);
		find_edge(the_node, flow, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 0));
}

int set_option(int option, t_list **visited, t_edge *the_edge, t_node *child)
{
	if (option == 1)
		return (!is_in(visited, child->name)
			&& the_edge->flow == 1
			&& the_edge->reverse && the_edge->reverse->flow == 0);
	if (option == 2)
		return (!is_in(visited, child->name)
			&& ((the_edge->flow == 1 && (the_edge->reverse && the_edge->reverse->flow == 0))
			|| (the_edge->flow == 0 && !the_edge->reverse)));
	return (0);
}

static void find_edge_set_opt(t_node *the_node, int option, t_list **queue, t_list **visited)
{
	t_dblist	*edges;
	t_edge	*the_edge;
	t_node	*child;

	edges = the_node->edges.head;
	while (edges)
	{
		the_edge = edges->content;
		child = the_edge->to;
		if (set_option(option, visited, the_edge, child))
		{
			child->parent = the_node;
			q_push (queue, child);
		}
		edges = edges->next;
	}
}

int bfs_path_search(t_farm *farm, int option)
{
	t_node *the_node;
	t_list *queue;
	t_list **visited;
	
	visited = (t_list **)ft_memalloc(HASH * sizeof(t_list *));
	queue = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
			return (free_and_exit_bfs(&queue, visited, 1));
		hashmap_set(visited, the_node->name, the_node);
		find_edge_set_opt(the_node, option, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 0));
}

static void create_rev_flow(t_node *the_node, t_dblist *edges, t_edge *the_edge)
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
					exit (1);
				the_edge->reverse->reverse = the_edge;
			}
			break ;
		}
		edges = edges->next;
	}
}

void update_res_flow(t_room *end)
{
	t_node	*the_node;
	t_edge	*the_edge;
	t_dblist	*edges;
	
	the_node = end->in;
	edges = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges.head;
		create_rev_flow(the_node, edges, the_edge);
		the_node = the_node->parent;
	}
}

static void set_edge_flow(t_node *the_node, t_dblist *edges, t_edge *the_edge, int flow)
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

/*static void set_edge_flow_new(t_node *the_node, t_dblist *edges, t_edge *the_edge, int flow)
{
	while (edges)
	{
		the_edge = edges->content;
		if (the_edge->to == the_node)
		{
			if (the_edge->reverse)
				the_edge->flow = flow;
			if (!the_edge->reverse)
				the_edge->flow = flow - 1;
			break ;
		}
		edges = edges->next;
	}
}*/

void update_fwd_flow(t_farm *farm, int flow)
{
	t_node	*the_node;
	t_edge	*the_edge;
	t_dblist	*edges;

	the_node = farm->end->in;
	edges = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges.head;
		//set_edge_flow_new(the_node, edges, the_edge, flow);
		while (edges)
		{
			the_edge = edges->content;
			if (the_edge->to == the_node)
			{
				if (the_edge->reverse)
					the_edge->flow = flow;
				if (!the_edge->reverse)
					the_edge->flow = flow - 1;
				break ;
			}
			edges = edges->next;
		}
		the_node = the_node->parent;
	}
}

t_list *mark_and_save_path(t_farm *farm, int flow)
{
	t_node *the_node;
	t_edge *the_edge;
	t_dblist *edges;
	t_list *the_path;

	the_node = farm->end->in;
	edges = NULL;
	the_path = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges.head;
		set_edge_flow(the_node, edges, the_edge, flow);
		if (the_node->source != farm->start && the_node->source != the_node->parent->source)
			ft_lstadd(&the_path, lstnew_pointer(the_node->source->name));
		the_node = the_node->parent;
	}
	return (the_path);
}

void reset_mark(t_farm *farm)
{
	while (bfs(farm, 2))
	{
		update_fwd_flow(farm, 1);
	}
}

/*void reset_all_flow(t_farm *farm)
{
	while (bfs(farm, 1))
	{
		update_fwd_flow(farm, 0);
	}
	while (bfs(farm, 2))
	{
		update_fwd_flow(farm, 0);
	}
}*/

static int    when_to_stop(int     *min_num_lines, t_list    **set_i, int index, t_farm *farm)
{
    int    num_lines;
    int    *queue;

    queue = get_numrooms(set_i, index);
    num_lines = count_printed_lines(farm->num_ants, queue, index);
    for (int i = 0; i < index; i++)
        printf("%d\n", queue[i]);
    printf("\n");
    if (num_lines >= *min_num_lines)
        return (1);
    else
        *min_num_lines = num_lines;
    return (0);
}

t_list *get_paths(t_farm *farm, int option)
{
	t_list	*sets;
	t_list	**set_i;
	t_list	**prev_set;
	size_t	i;
	size_t	j;
	int		min_num_lines;
	
	i= 0;
	prev_set = NULL;
	min_num_lines = INT_MAX;
	sets = NULL;
	/*if (option == 2)
	    reset_all_flow(farm);*/
	while(bfs(farm, 0))
	{
		update_res_flow(farm->end);
		set_i = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *));
		if (i > 0)
			reset_mark(farm);
		j = 0;
		while (j < i + 1 && bfs_path_search(farm, option))
		{
			set_i[j] = mark_and_save_path(farm, 2); //set fwd edge to 2
			j++;
		}
		if (j)
			ft_lstappend(&sets, lstnew_pointer(set_i));
		i++;
		//printf("YES\n");
		if (when_to_stop(&min_num_lines, set_i, j, farm))
		{
			send_ants(farm->num_ants, prev_set, j - 1);
			exit(1);
		}
		prev_set = set_i;
	}
	return (sets);
}


// to see add_one_more_set(t_list *sets, t_farm *farm, size_t size) go to test_one_path_set branch