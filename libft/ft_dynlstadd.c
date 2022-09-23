/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynlstadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:28:13 by ykot              #+#    #+#             */
/*   Updated: 2022/09/20 12:53:23 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dynlstadd(t_dynlist *alst, t_dblist *new)
{
	if (!new)
		return ;
	if (alst->size == 0)
	{
		alst->head = new;
		alst->tail = new;
		alst->size = 1;
	}	
	else
	{
		new->next = alst->head;
		alst->head->prev = new;
		alst->head = new;
		alst->size++;
	}
}
