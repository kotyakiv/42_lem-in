/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:52:36 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 14:08:18 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_get_paths(size_t *i, t_pathsets *pathsets, int option)
{
	*i = 0;
	pathsets->path_set = NULL;
	pathsets->prev_set = NULL;
	pathsets->min_num_lines = INT_MAX;
	pathsets->option = option;
}

static t_list	**free_sets_null(t_pathsets *pathsets, size_t i)
{
	free_sets(pathsets, i);
	return (NULL);
}

static void	free_sets_err(t_farm *farm, t_pathsets *pathsets, size_t i)
{
	free_sets(pathsets, i);
	err_nolines(farm, ERR_MEM_ALLOC);
}

static t_list	**exit_get_paths(t_farm *farm, t_pathsets *pathsets,
							size_t i, int res_to_stop)
{
	if (res_to_stop == -1)
		free_sets_err(farm, pathsets, i);
	if (res_to_stop == 1)
		return (return_prev_set(farm, pathsets, pathsets->option, i));
	return (free_sets_null(pathsets, i));
}

/*
	When the flow is zero find the shortest node-disjoint path
	and create the reverse edges for that path.
	Call the bfs_path with the given option, 
	mark the edge flow of the found path with 2 and save the path-set.
	Check if the previous path-set provides less lines than 
	the current path-set for the given ant number,
	if so return the previous path-set
*/
t_list	**get_paths(t_farm *farm, int option)
{
	t_pathsets	pathsets;
	size_t		i;
	size_t		j;
	int			res_to_stop;

	init_get_paths(&i, &pathsets, option);
	bfs_reset(farm);
	while (bfs(farm, 0))
	{
		update_res_flow(farm);
		pathsets.path_set = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *));
		if (pathsets.path_set == NULL)
			free_sets_err(farm, &pathsets, i);
		j = 0;
		while (j < i + 1 && bfs_path(farm, option))
			pathsets.path_set[j++] = mark_and_save_path(farm, 2);
		i++;
		reset_mark(farm);
		res_to_stop = when_to_stop(&pathsets, i, farm);
		if (res_to_stop != 0)
			return (exit_get_paths(farm, &pathsets, i, res_to_stop));
		free_path_set(pathsets.prev_set, i - 1);
		pathsets.prev_set = pathsets.path_set;
	}
	return (return_curr_set(farm, pathsets.path_set, option, i));
}
