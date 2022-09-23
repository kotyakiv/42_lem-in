/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:06:25 by ykot              #+#    #+#             */
/*   Updated: 2022/09/20 12:52:01 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dblstdel(t_dynlist *alst, void (*del)(void *))
{
	t_dblist	*next;
	t_dblist *temp;
	
	if (alst->size == 0)
		return ;
	temp = alst->head;
	while (temp)
	{
		next = temp->next;
		ft_dblstdelone(&temp, del);
		temp = next;
	}
	alst = NULL;
}
