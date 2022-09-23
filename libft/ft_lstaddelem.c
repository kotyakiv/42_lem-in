/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 00:56:34 by ykot              #+#    #+#             */
/*   Updated: 2022/03/17 11:40:49 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddelem(t_list **alst, t_list *new, size_t pos)
{
	t_list	*begin_lst;
	size_t	i;

	++pos;
	if (!new || !pos || ft_lstsize(*alst) < pos - 1)
		return ;
	if (pos == 1)
		ft_lstadd(&(*alst), new);
	else
	{
		i = 1;
		begin_lst = *alst;
		while (i < pos - 1)
		{
			*alst = (*alst)->next;
			++i;
		}
		new->next = (*alst)->next;
		(*alst)->next = new;
		*alst = begin_lst;
	}
}
