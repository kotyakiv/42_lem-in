/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_fn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:16:18 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/09 23:01:32 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_dblfn(void *content)
{
	if (content)
		free(content);
}

void	null_fn(void *content, size_t size)
{
	content = NULL;
	size++;
}

void	del(void *content, size_t size)
{
	if (content)
		free(content);
	size++;
}

void	del_rooms(void *content)
{
	t_room	*the_room;

	the_room = content;
	ft_strdel(&the_room->name);
	if (the_room->in)
	{
		ft_strdel(&the_room->in->name);
		ft_dblstdel(&the_room->in->edges, del_dblfn);
		ft_memdel((void **)&the_room->in);
	}
	if (the_room->out)
	{
		ft_strdel(&the_room->out->name);
		ft_dblstdel(&the_room->out->edges, del_dblfn);
		ft_memdel((void **)&the_room->out);
	}
	ft_memdel((void **)&the_room);
}
