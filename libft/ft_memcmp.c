/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:27:09 by ykot              #+#    #+#             */
/*   Updated: 2021/11/23 14:37:54 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*n1;
	const unsigned char	*n2;
	size_t				i;

	n1 = (const unsigned char *)s1;
	n2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (n1[i] != n2[i])
			return (n1[i] - n2[i]);
		++i;
	}
	return (0);
}
