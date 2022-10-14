/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynlstdelelem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:46:55 by ykot              #+#    #+#             */
/*   Updated: 2022/10/06 16:58:35 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del_head(t_dynlist *alst, void (*del)(void *))
{
	t_dblist	*temp;
	t_dblist	*next;

	temp = alst->head;
	next = temp->next;
	ft_dblstdelone(&(temp->prev), del);
	next->prev = NULL;
	alst->head = next;
	alst->size--;
}

static void	del_tail(t_dynlist *alst, void (*del)(void *))
{
	t_dblist	*temp;
	t_dblist	*prev;

	temp = alst->tail;
	prev = temp->prev;
	ft_dblstdelone(&(prev->next), del);
	temp->next = NULL;
	alst->tail = prev;
	alst->size--;
}

static void	del_midelem(t_dynlist *alst, size_t elem, void (*del)(void *))
{
	t_dblist	*temp;
	t_dblist	*next;
	t_dblist	*prev;

	temp = ft_dynlstelem(*alst, elem);
	next = temp->next;
	prev = temp->prev;
	ft_dblstdelone(&temp, del);
	prev->next = next;
	next->prev = prev;
	alst->size--;
}

void	ft_dynlstdelelem(t_dynlist *alst, size_t elem, void (*del)(void *))
{
	if (alst->size == 0 || elem > alst->size - 1)
		return ;
	if (elem == 0)
	{
		del_head(alst, del);
		return ;
	}
	if (elem == alst->size - 1)
	{
		del_tail(alst, del);
		return ;
	}
	del_midelem(alst, elem, del);
}
