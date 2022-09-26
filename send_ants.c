/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:39 by ykot              #+#    #+#             */
/*   Updated: 2022/09/26 00:02:37 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	*get_numrooms(t_list **paths, int size)
{
	int	*rooms;
	int	i;
	
	rooms = (int *)ft_memalloc((size_t)(sizeof(int) * size));
	if (rooms == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		rooms[i] = ft_lstsize(paths[i]);
		if (rooms[i] == 0)
			return (NULL);
		++i;
	}
	return (rooms);
}

t_list	**make_queue(t_farm *farm, t_list **paths, int size)
{
	t_list	**queue;
	int		*rooms;
	int		j;

	queue = (t_list **)ft_memalloc(sizeof(t_list *) * size);
	if (queue == NULL)
		return (NULL);
	rooms = get_numrooms(paths, size);
	if (rooms == NULL)
	{
		free(queue);
		return (NULL);
	}
	j = 0;
	while (farm->num_ants--)
	{
		if (j + 1 != size && rooms[j] + (int)(ft_lstsize(queue[j])) > rooms[j + 1])
		{
			j++;
			if (ant_push(paths[j], &queue[j]))
			{
				ft_lstdel(queue, del);
				free(queue);
				free(rooms);
				return (NULL);
			}
		}
		else
		{
			j = 0;
			if (ant_push(paths[j], &queue[j]))
			{
				ft_lstdel(queue, del);
				free(queue);
				free(rooms);
				return (NULL);
			}
		}
	}
	free(rooms);
	return (queue);
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
		error(farm, "Memory allocation");
	ant_pop(&queue, &moving_ants, size, &cur_ant_num);
	while (moving_ants)
	{
		move_all_ants(&moving_ants);
		ant_pop(&queue, &moving_ants, size, &cur_ant_num);
	}
	free(queue);
}

int count_printed_lines(int num_ants, int *queue, int size)
{
	int	i;

	i = 0;	
	while (num_ants--)
	{
		if (i + 1 != size && queue[i] > queue[i + 1])
		{
			i++;
			queue[i]++;
		}
		else
		{
			i = 0;
			queue[i]++;
		}
	}
	return (queue[0]);
}

static void	print_flag_p(t_farm *farm, int nl1, int nl2)
{
	if (nl1 < nl2)
	{
		
		print_paths(farm, farm->option1, farm->index.ind1);
		if (!farm->flag.v)
			ft_printf("Number of lines to print: %d\n", nl1 - 1);
	}
	else
	{
		print_paths(farm, farm->option2, farm->index.ind2);
		if (!farm->flag.v)
			ft_printf("Number of lines to print: %d\n", nl2 - 1);
	}
}

void	find_the_best_paths_and_send_ants(t_farm *farm)
{
    int    	num_lines_1;
	int    	num_lines_2;
    int    	*queue;

    queue = get_numrooms(farm->option1, farm->index.ind1);
	if (queue == NULL)
		err_nolines(farm, "Memory allocation");
    num_lines_1 = count_printed_lines(farm->num_ants, queue, farm->index.ind1);
	free(queue);
	queue = get_numrooms(farm->option2, farm->index.ind2);
	if (queue == NULL)
		err_nolines(farm, "Memory allocation");
    num_lines_2 = count_printed_lines(farm->num_ants, queue, farm->index.ind2);
	free(queue);
	if (farm->flag.p || farm->flag.v)
		print_flag_p(farm, num_lines_1, num_lines_2);
	if (!farm->flag.p)
	{
		if (num_lines_1 < num_lines_2)
			send_ants(farm, farm->option1, farm->index.ind1);
		else
			send_ants(farm, farm->option2, farm->index.ind2);
	}
	if (farm->flag.v)
		ft_putendl("");
}
