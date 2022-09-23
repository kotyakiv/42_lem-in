/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:06:04 by ykot              #+#    #+#             */
/*   Updated: 2022/09/20 12:52:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dblstdelone(t_dblist **alst, void (*del)(void*))
{
	if (!alst || !*alst)
		return ;
	del((*alst)->content);
	free(*alst);
	*alst = NULL;
}
