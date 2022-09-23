/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:38:46 by ykot              #+#    #+#             */
/*   Updated: 2021/11/23 14:37:12 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstsize(t_list *begin_list)
{
	size_t	size;

	size = 0;
	if (!begin_list)
		return (0);
	while (begin_list)
	{
		begin_list = begin_list->next;
		++size;
	}
	return (size);
}
