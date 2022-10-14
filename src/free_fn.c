/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:46:05 by ykot              #+#    #+#             */
/*   Updated: 2022/10/10 11:51:00 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_split(char ***str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
	{
		ft_strdel(&((*str)[i]));
		i++;
	}
	ft_memdel((void *)str);
}

void	free_path_set(t_list **path_set, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (path_set[i])
		{
			ft_lstdel(&path_set[i], null_fn);
		}
		i++;
	}
	free(path_set);
}

void	free_farm(t_farm *farm)
{
	if (farm->rooms.head)
		ft_dblstdel(&farm->rooms, del_rooms);
	if (farm->input_lines.head)
		ft_dblstdel(&farm->input_lines, del_dblfn);
	free_path_set(farm->option1, farm->index.ind1);
	free_path_set(farm->option2, farm->index.ind2);
	if (farm->hashmap)
		free_hashmap(farm->hashmap);
}
