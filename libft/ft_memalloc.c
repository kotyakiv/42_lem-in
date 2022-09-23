/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:42:30 by ykot              #+#    #+#             */
/*   Updated: 2021/11/02 15:50:35 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*allocated_memory;
	size_t	i;

	allocated_memory = (void *)malloc(size);
	if (!allocated_memory)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((unsigned char *)allocated_memory)[i] = 0;
		++i;
	}
	return (allocated_memory);
}
