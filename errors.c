/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:43:14 by ykot              #+#    #+#             */
/*   Updated: 2022/07/14 14:54:48 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	del(void *content, size_t size)
{
	ft_memdel(&content);
	(void *)size;
}

static void	del_rooms(void *content, size_t size)
{
	/*ft_lstdel(content.);*/
	ft_memdel(&content);
	(void *)size;
}

void	error(t_list **rooms)
{
	ft_lstdel(rooms, del_rooms);
	ft_putendl_fd("Error", 2);
	exit(1);
}
