/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynlstadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:28:13 by ykot              #+#    #+#             */
/*   Updated: 2022/10/06 16:46:06 by ykot             ###   ########.fr       */
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
