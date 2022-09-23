/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:43:14 by ykot              #+#    #+#             */
/*   Updated: 2022/09/23 01:36:12 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*void	lstdel(t_list **alst) //still need this to free hashmap list?!?!
{
	t_list	*curr;
	t_list	*next;

	if (!alst || !*alst)
		return ;
	curr = *alst;
	while (curr)
	{
		next = curr->next;
		if (curr->content_size)
			free(curr->content);
		free(curr);
		curr = next;
	}
	*alst = NULL;
}*/

static void del_fn(void *content)
{
	if (content)
		free(content);
}

static void	del_rooms(void *content)
{
	t_room *the_room;

	the_room = content;
	ft_strdel(&the_room->name);
	if (the_room->in)  //node_in
	{
		ft_strdel(&the_room->in->name);
		ft_dblstdel(&the_room->in->edges, del_fn);
		ft_memdel((void **)&the_room->in);
	}
	if (the_room->out)  //node_out
	{
		ft_strdel(&the_room->out->name);
		ft_dblstdel(&the_room->out->edges, del_fn);
		ft_memdel((void **)&the_room->out);
	}
	ft_memdel((void **)&the_room);
}

void	free_farm(t_farm *farm)
{
	ft_dblstdel(&farm->rooms, del_rooms);
	//ft_lstdel(&farm->links, del_fn);
	free_hashmap(farm->hashmap);
}

void	error(t_farm *farm, char *er_str)
{
	free_farm(farm);
	ft_putstr_fd("Error: ", 2);
	if (!farm->no_errlines)
	{
		ft_putstr_fd("in line ", 2);
		ft_putnbr_fd(farm->read_lines, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(er_str, 2);
	//system("leaks lem-in >> error_leaks.txt");
	exit(1);
}

void	free_split(char ***str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
	{
		ft_strdel(&((*str)[i]));
		i++;
	}
	ft_memdel((void *)str);
}

void	error_free_split_line(t_farm *farm, char ***str, char **line, char *er_str)
{
	free_split(str);
	ft_strdel(line);
	error(farm, er_str);
}
