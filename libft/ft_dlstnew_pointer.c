/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:03:10 by ykot              #+#    #+#             */
/*   Updated: 2022/10/06 16:01:06 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblstnew_pointer(void *content)
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
