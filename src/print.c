/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:05:24 by ykot              #+#    #+#             */
/*   Updated: 2022/10/06 16:05:32 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	iterate_list_print_room(t_farm *farm, t_list *list)
{
	char	*the_room;

	while (list)
	{
		the_room = list->content;
		if (farm->flag.v)
			ft_printf("%s ", the_room);
		else
			ft_printf("%s > ", the_room);
		list = list->next;
	}
}

void	print_paths(t_farm *farm, t_list **paths, size_t flow)
{
	size_t	i;
	t_list	*list;
	size_t	len;

	i = 0;
	while (i < flow)
	{
		list = paths[i];
		if (!list)
			break ;
		len = ft_lstsize(paths[i]);
		if (farm->flag.v)
			ft_printf("%s ", farm->start->name);
		iterate_list_print_room(farm, list);
		if (farm->flag.p)
			ft_printf(" -path_len: %d- ", (int)len);
		if (!farm->flag.v)
			ft_putendl("");
		ft_putendl("");
		i++;
	}
	ft_putendl("");
}

static	void	print_input(t_farm farm)
{
	t_dblist	*tempptr;

	tempptr = farm.input_lines.head;
	while (tempptr)
	{
		ft_putendl((char *)tempptr->content);
		tempptr = tempptr->next;
	}
}

void	print_farm(t_farm farm)
{
	print_input(farm);
	ft_putendl("");
}
