/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:05:24 by ykot              #+#    #+#             */
/*   Updated: 2022/09/20 13:19:27 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	print_rooms(t_farm farm)
{
	t_dblist	*rooms;
	t_room	*the_room;

	rooms = farm.rooms.head;
	while (rooms)
	{
		the_room = rooms->content;
		if (ft_strequ(farm.start->name, the_room->name))
		{
			ft_putendl("##start");
		}
		else if (ft_strequ(farm.end->name, the_room->name))
		{
			ft_putendl("##end");
		}
		printf("%s %d %d\n", the_room->name, the_room->coord.x, the_room->coord.y);
		//printf("%s %d %d %lu\n", the_room->name, the_room->coord.x, the_room->coord.y, hash(the_room->name, HASH));
		rooms = rooms->next;
	}
}

/*static void	print_links(t_farm farm)
{
	t_list	*links;

	links = farm.links;
	while (links)
    {
        ft_putendl((char *)links->content);
        links = links->next;
    }
}*/

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
/*
static void print_comments(t_farm farm)
{
	t_list	*comments;
	char	*the_comment;

	comments = farm.comments;
	while (comments)
	{
		the_comment = comments->content;
		ft_putendl(the_comment);
		comments = comments->next;
	}
	//free comments list here ?
}
*/
void print_paths(t_list **paths, size_t flow)
{
	size_t i;
	char *the_room;
	t_list *list;
	size_t len;

	i = 0;
	while (i < flow)
	{
		list = paths[i];
		if (!list)
			break ;
		len = ft_lstsize(paths[i]);
		while (list)
		{
			the_room = list->content;
			printf("%s > ", the_room);
			list = list->next;
		}
		printf(" -path_len: %d- ", (int)len);
		printf("\n\n");
		i++;
	}
}

void print_path_sets(t_list *sets)
{
	size_t i;
	t_list **the_set;
	t_list *curr;

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

static	void	print_input(t_farm farm)
{
	t_dblist *tempptr;

	tempptr = farm.input_lines.head;
	while (tempptr)
	{
		ft_putendl((char *)tempptr->content);
		tempptr = tempptr->next;
	}
}

void	print_farm(t_farm farm)
{
	/*ft_printf("%d\n", farm.num_ants);
	print_rooms(farm);
	print_links(farm);
	print_comments(farm);*/
	print_input(farm);
	ft_putendl("---");
	//print_adj_list(farm);
	ft_putendl("");
}

