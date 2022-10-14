/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:49:37 by ykot              #+#    #+#             */
/*   Updated: 2022/10/09 18:02:51 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*strnew;
	size_t	i;

	strnew = (char *)malloc(sizeof(char) * (size + 1));
	if (!strnew)
		return (NULL);
	i = 0;
	while (i < size + 1)
	{
		strnew[i] = '\0';
		++i;
	}
	return (strnew);
}
