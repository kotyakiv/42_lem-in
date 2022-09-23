/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:04:40 by ykot              #+#    #+#             */
/*   Updated: 2021/11/08 13:03:57 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*new;
	t_list	*temp;

	if (!lst)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new = f(lst);
		if (!new)
			return (NULL);
		if (!new_list)
		{
			new_list = new;
			temp = new_list;
		}
		else
		{
			temp->next = new;
			temp = new;
		}
		lst = lst->next;
	}
	return (new_list);
}
