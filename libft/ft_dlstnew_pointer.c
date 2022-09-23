/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:03:10 by ykot              #+#    #+#             */
/*   Updated: 2022/09/20 12:52:56 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblstnew_pointer(void *content)  //where to put this fn, we are using this in checks.c get_rooms.c and hash.c and bfs.c
{
	t_dblist	*lstnew;

	lstnew = (t_dblist *)ft_memalloc(sizeof(t_dblist));
	if (!lstnew)
		return (NULL);
	if (!content)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
		lstnew->next = NULL;
        lstnew->prev = NULL;
	}
	else
	{
		lstnew->content = content;
		lstnew->content_size = 0;
		lstnew->next = NULL;
        lstnew->prev = NULL;
	}
	return (lstnew);
}