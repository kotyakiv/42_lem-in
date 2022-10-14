/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:39 by ykot              #+#    #+#             */
/*   Updated: 2022/10/10 14:39:18 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	**exit_make_queue(t_list **queue, int *rooms)
{
	ft_lstdel(queue, del);
	free(queue);
	free(rooms);
	return (NULL);
}

/* Make a queue of ants for every path, some paths could be without any ant */
t_list	**make_queue(t_farm *farm, t_list **paths, int size)
{
	t_list	**q;
	int		*rooms;
	int		j;

	q = (t_list **)ft_memalloc(sizeof(t_list *) * size);
	if (q == NULL)
		return (NULL);
	rooms = get_numrooms(paths, size);
	if (rooms == NULL)
	{
		free(q);
		return (NULL);
	}
	j = 0;
	while (farm->num_ants--)
	{
		if (j + 1 != size && rooms[j] + (int)(ft_lstsize(q[j])) > rooms[j + 1])
			j++;
		else
			j = 0;
		if (ant_push(paths[j], &q[j]))
			return (exit_make_queue(q, rooms));
	}
	free(rooms);
	return (q);
}

static void	move_all_ants(t_list **moving_ants)
{
	t_list	*iter;
	int		i;
	t_ant	*ant;

	i = 0;
	iter = *moving_ants;
	while (iter)
	{
		ant = (t_ant *)iter->content;
		print_ant(*ant);
		if (iter->next == NULL)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		move_ant(ant);
		if (ant->pathptr == NULL)
		{
			iter = iter->next;
			ft_lstdelelem(moving_ants, i, del);
			continue ;
		}
		i++;
		iter = iter->next;
	}
}

void	send_ants(t_farm *farm, t_list **paths, int size)
{
	t_list	**queue;
	t_list	*moving_ants;
	int		cur_ant_num;

	moving_ants = NULL;
	cur_ant_num = 1;
	queue = make_queue(farm, paths, size);
	if (queue == NULL)
		err_nolines(farm, ERR_MEM_ALLOC);
	ant_pop(&queue, &moving_ants, size, &cur_ant_num);
	print_farm(*farm);
	if (farm->flag.v)
		print_paths(farm, paths, size);
	while (moving_ants)
	{
		move_all_ants(&moving_ants);
		ant_pop(&queue, &moving_ants, size, &cur_ant_num);
	}
	free(queue);
}
