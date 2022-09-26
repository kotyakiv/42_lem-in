/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:46:05 by ykot              #+#    #+#             */
/*   Updated: 2022/09/25 20:11:50 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void del_dblfn(void *content)
{
	if (content)
		free(content);
}

void null_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void	del(void  *content, size_t size)
{
	free(content);
	size = 0;
}

static void	del_rooms(void *content)
{
	t_room *the_room;

	the_room = content;
	ft_strdel(&the_room->name);
	if (the_room->in)  //node_in
	{
		ft_strdel(&the_room->in->name);
		ft_dblstdel(&the_room->in->edges, del_dblfn);
		ft_memdel((void **)&the_room->in);
	}
	if (the_room->out)  //node_out
	{
		ft_strdel(&the_room->out->name);
		ft_dblstdel(&the_room->out->edges, del_dblfn);
		ft_memdel((void **)&the_room->out);
	}
	ft_memdel((void **)&the_room);
}

void	free_set_i(t_list **set_i, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (set_i[i])
		{
			ft_lstdel(&set_i[i], null_fn);
		}
		i++;
	}
	free(set_i);
}

void	free_farm(t_farm *farm)
{
	ft_dblstdel(&farm->rooms, del_rooms);
    ft_dblstdel(&farm->input_lines, del_dblfn);
    free_set_i(farm->option1, farm->index.ind1);
	free_set_i(farm->option2, farm->index.ind2);
	//ft_lstdel(&farm->links, del_fn);
	free_hashmap(farm->hashmap);
}
