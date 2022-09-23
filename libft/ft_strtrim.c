/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 20:04:59 by ykot              #+#    #+#             */
/*   Updated: 2021/11/23 15:26:23 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*newstr;
	size_t	ns;
	size_t	nl;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	ns = 0;
	while (ns < s_len && (s[ns] == ' ' || s[ns] == '\t' || s[ns] == '\n'))
		++ns;
	nl = s_len;
	while (--nl && (s[nl] == ' ' || s[nl] == '\t' || s[nl] == '\n'))
		;
	newstr = ft_strsub(s, ns, nl - ns + 1);
	return (newstr);
}
