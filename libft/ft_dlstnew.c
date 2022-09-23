/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:06:27 by ykot              #+#    #+#             */
/*   Updated: 2022/09/20 12:53:14 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblstnew(void const *content, size_t content_size)
{
	t_dblist	*dlstnew;

	dlstnew = (t_dblist *)malloc(sizeof(t_dblist));
	if (!dlstnew)
		return (NULL);
	if (!content)
	{
		dlstnew->content = NULL;
		dlstnew->content_size = 0;
		dlstnew->next = NULL;
        dlstnew->prev = NULL;
	}
	else
	{
		dlstnew->content = (void *)malloc(content_size);
		if (!dlstnew->content)
		{
			free(dlstnew);
			return (NULL);
		}
		ft_memcpy(dlstnew->content, content, content_size);
		dlstnew->content_size = content_size;
		dlstnew->next = NULL;
        dlstnew->prev = NULL;
	}
	return (dlstnew);
}
