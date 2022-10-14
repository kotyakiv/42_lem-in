/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:13:13 by ykot              #+#    #+#             */
/*   Updated: 2022/10/14 14:44:03 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* Get number of rooms from each path */
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
		++i;
	}
	return (rooms);
}

/* How many lines are going to be printed using these paths */
int	count_printed_lines(int num_ants, int *queue, int size)
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

/* Printing only paths and number of lines, without sending ants */
static void	print_flag_p(t_farm *farm, int nl1, int nl2)
{
	if (nl1 < nl2)
	{
		print_paths(farm, farm->option1, farm->index.ind1);
		ft_printf("Number of lines to print: %d\n", nl1 - 1);
	}
	else
	{
		print_paths(farm, farm->option2, farm->index.ind2);
		ft_printf("Number of lines to print: %d\n", nl2 - 1);
	}
}

static int	lines_to_print(t_farm *farm, t_list **option, int index)
{
	int	*queue;
	int	num_lines;

	queue = get_numrooms(option, index);
	if (queue == NULL)
		err_nolines(farm, ERR_MEM_ALLOC);
	num_lines = count_printed_lines(farm->num_ants, queue, index);
	free(queue);
	return (num_lines);
}

/* The best paths for current number of ants */
void	find_the_best_paths_and_send_ants(t_farm *farm)
{
	int	num_lines_1;
	int	num_lines_2;

	num_lines_1 = lines_to_print(farm, farm->option1, farm->index.ind1);	
	if (farm->option2 == NULL)
	{
		if (farm->flag.p)
		{
			print_paths(farm, farm->option1, farm->index.ind1);
			ft_printf("Number of lines to print: %d\n", num_lines_1 - 1);
			return ;
		}
		send_ants(farm, farm->option1, farm->index.ind1);
		return ;
	}
	num_lines_2 = lines_to_print(farm, farm->option2, farm->index.ind2);
	if (farm->flag.p)
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
