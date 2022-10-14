/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:43:58 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 00:53:44 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	q_push(t_list **queue, t_node *the_node)
{
	t_list	*to_push;

	to_push = ft_lstnew_pointer(the_node);
	if (!to_push)
		return (0);
	ft_lstappend(queue, to_push);
	return (1);
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

void	free_err_hashmap(t_farm *farm, t_list	**queue, t_list **visited)
{
	if (queue != NULL && *queue != NULL)
		ft_lstdel(queue, null_fn);
	if (*visited != NULL && visited != NULL)
		free_hashmap(visited);
	err_nolines(farm, ERR_MEM_ALLOC);
}
