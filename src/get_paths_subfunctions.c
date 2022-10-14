/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_subfunctions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:06:28 by ykot              #+#    #+#             */
/*   Updated: 2022/10/06 15:09:49 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	when_to_stop(t_pathsets *pathsets, int index, t_farm *farm)
{
	int	num_lines;
	int	*queue;

	queue = get_numrooms(pathsets->path_set, index);
	if (queue == NULL)
		return (-1);
	if (check_path_size(queue, index))
	{
		free(queue);
		return (-2);
	}
	num_lines = count_printed_lines(farm->num_ants, queue, index);
	if (num_lines > pathsets->min_num_lines)
	{
		free(queue);
		return (1);
	}
	else
		pathsets->min_num_lines = num_lines;
	free(queue);
	return (0);
}

void	free_sets(t_pathsets *pathsets, int i)
{
	if (pathsets->path_set != NULL)
		free_path_set(pathsets->path_set, i);
	if (pathsets->prev_set != NULL)
		free_path_set(pathsets->prev_set, i - 1);
}

t_list	**return_prev_set(t_farm *farm, t_pathsets *pathsets,
								int option, size_t i)
{
	free_path_set(pathsets->path_set, i);
	if (option == 1)
		farm->index.ind1 = i - 1;
	else
		farm->index.ind2 = i - 1;
	return (pathsets->prev_set);
}

t_list	**return_curr_set(t_farm *farm, t_list **path_set,
								int option, size_t i)
{
	if (option == 1)
		farm->index.ind1 = i;
	else
		farm->index.ind2 = i;
	return (path_set);
}
