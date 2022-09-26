/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:43:58 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/25 15:56:36 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	q_push(t_list **queue, t_node *the_node)
{
	t_list	*to_push;

	to_push = lstnew_pointer(the_node);
	if (!to_push)
		return ;
	ft_lstappend(queue, to_push);
}

t_node	*q_pop(t_list **queue)
{
	t_node	*the_node;

	if (!queue)
		return (NULL);
	the_node = (*queue)->content;
	ft_lstdelelem(queue, 0, null_fn);
	return (the_node);
}

int	free_and_exit_bfs(t_list **queue, t_list **visited, int exit)
{
	ft_lstdel(queue, null_fn);
	free_hashmap(visited);
	return (exit);
}
