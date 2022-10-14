/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:06:27 by ykot              #+#    #+#             */
/*   Updated: 2022/10/06 16:52:52 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_zero_content(t_dblist	*dlstnew)
{
	dlstnew->content = NULL;
	dlstnew->content_size = 0;
	dlstnew->next = NULL;
	dlstnew->prev = NULL;
}

t_dblist	*ft_dblstnew(void const *content, size_t content_size)
{
	t_dblist	*dlstnew;

	dlstnew = (t_dblist *)malloc(sizeof(t_dblist));
	if (!dlstnew)
		return (NULL);
	if (!content)
		init_zero_content(dlstnew);
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
