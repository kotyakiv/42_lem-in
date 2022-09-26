/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:05:24 by ykot              #+#    #+#             */
/*   Updated: 2022/09/25 23:38:24 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*static void print_adj_list(t_farm farm) //just to see what we have in adj_list, will be removed later
{
	t_list *rooms;
	t_room *the_room;
	t_list	*edges;
	t_edge	*the_edge;

	rooms = farm.rooms;
	while (rooms)
	{
		the_room = rooms->content;
		printf("the room %s:\n", the_room->name);
		if (the_room->in)
		{
			printf("%s -> ",the_room->in->name);
			edges = the_room->in->edges;
			while (edges)
			{
				the_edge = edges->content;
				printf("%s (flow: %d) - ", the_edge->to->name, the_edge->flow);
				edges = edges->next;
			}
			printf("\n");
		}
		if (the_room->out)
		{
			printf("%s -> ", the_room->out->name);
			edges = the_room->out->edges;
			while (edges)
			{
				the_edge = edges->content;
				printf("%s (flow: %d) - ", the_edge->to->name, the_edge->flow);
				edges = edges->next;
			}
			printf("\n");
		}
		rooms = rooms->next;
	}
}*/

void	print_paths(t_farm *farm, t_list **paths, size_t flow)
{
	size_t	i;
	char	*the_room;
	t_list	*list;
	size_t	len;

	i = 0;
	while (i < flow)
	{
		list = paths[i];
		if (!list)
			break ;
		len = ft_lstsize(paths[i]);
		if (farm->flag.v)
			ft_printf("%s ", farm->start->name);
		while (list)
		{
			the_room = list->content;
			if (farm->flag.v)
				ft_printf("%s ", the_room);
			else
				ft_printf("%s > ", the_room);
			list = list->next;
		}
		if (farm->flag.p)
			ft_printf(" -path_len: %d- ", (int)len);
		if (!farm->flag.v)
			ft_putendl("");
		ft_putendl("");
		i++;
	}
	ft_putendl("");
}

/*
void	print_path_sets(t_list *sets)
{
	size_t	i;
	t_list	**the_set;
	t_list	*curr;

	i = 0;
	curr = sets;
	while (curr)
	{
		the_set = curr->content;
		printf("set %d:\n", (int)i);
		print_paths(the_set, i + 1);
		i++;
		curr = curr->next;
	}
}
*/
static	void	print_input(t_farm farm)
{
	t_dblist	*tempptr;

	tempptr = farm.input_lines.head;
	while (tempptr)
	{
		ft_putendl((char *)tempptr->content);
		tempptr = tempptr->next;
	}
}

void	print_farm(t_farm farm)
{
	print_input(farm);
	//ft_putendl("---");
	ft_putendl("");
}
