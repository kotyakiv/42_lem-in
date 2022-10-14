/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:49:34 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/30 22:50:28 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_pointer(void *content)
{
	t_list	*lstnew;

	lstnew = (t_list *)ft_memalloc(sizeof(t_list));
	if (!lstnew)
		return (NULL);
	if (!content)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	else
	{
		lstnew->content = content;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	return (lstnew);
}
