/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:28:34 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 12:02:34 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned long	hash(const char *s, unsigned long m)
{
	unsigned long		key;
	unsigned const char	*us;

	us = (unsigned const char *) s;
	key = 0;
	while (*us != '\0')
	{
		key = (key * 256 + *us) % m;
		us++;
	}
	return (key);
}

int	hashmap_set(t_list **hashmap, char *str, void *ptr)
{
	t_list			*new;
	t_hash			*value;
	unsigned long	key;

	value = (t_hash *)ft_memalloc(sizeof(t_hash));
	if (value == NULL)
		return (0);
	value->name = str;
	value->ptr = ptr;
	key = hash(str, HASH);
	new = ft_lstnew_pointer((void *)value);
	if (!new)
	{
		free(value);
		return (0);
	}
	ft_lstappend(&hashmap[key], new);
	return (1);
}

void	*hashmap_get(t_list **hashmap, char *str)
{
	unsigned long	key;
	t_list			*curr;
	t_hash			*the_value;

	key = hash(str, HASH);
	curr = hashmap[key];
	while (curr)
	{
		the_value = curr->content;
		if (ft_strequ(the_value->name, str))
			return (the_value->ptr);
		curr = curr->next;
	}
	return (NULL);
}

int	is_in(t_list **hashmap, char *str)
{
	unsigned long	key;
	t_list			*curr;
	t_hash			*the_value;

	key = hash(str, HASH);
	curr = hashmap[key];
	while (curr)
	{
		the_value = curr->content;
		if (ft_strequ(the_value->name, str))
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

void	free_hashmap(t_list **hashmap)
{
	size_t	i;

	i = 0;
	while (i < HASH)
	{
		if (hashmap[i])
		{
			ft_lstdel(&hashmap[i], del);
		}
		i++;
	}
	free(hashmap);
}
