/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynlstdelelem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:07:10 by ykot              #+#    #+#             */
/*   Updated: 2022/09/20 12:53:51 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_dynlstdelelem(t_dynlist *alst, size_t elem, void (*del)(void *))
{
	t_dblist *temp;
    t_dblist *next;
    t_dblist *prev;
    
    if (alst->size == 0 || elem > alst->size - 1)
        return ;
    if (elem == 0)
    {
        temp = alst->head;
        next = temp->next;
        ft_dblstdelone(&(temp->prev), del);
        next->prev = NULL;
        alst->head = next;
        alst->size--;
        return ;
    }
    if (elem == alst->size - 1)
    {
        temp = alst->tail;
        prev =temp->prev;
        ft_dblstdelone(&(temp->next), del);
        temp->next = NULL;
        alst->tail = prev;
        alst->size--;
        return ;
    }
    temp = ft_dynlstelem(*alst, elem);
    next = temp->next;
    prev = temp->prev;
    ft_dblstdelone(&temp, del);
    prev->next = next;
    next->prev = prev;
    alst->size--;
}
