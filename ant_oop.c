/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_oop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:57:05 by ykot              #+#    #+#             */
/*   Updated: 2022/08/02 23:52:52 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_ant *new_ant(int num, t_list *pathptr)
{
    t_ant   *new;

    new = (t_ant *)ft_memalloc(sizeof(t_ant));
    if (new == NULL)
        return (NULL);
    new->name = num;
    new->pathptr = pathptr;
    return(new);
}

static void    del_ant(t_ant **ant)
{
    ft_memdel((void **)ant);
}

void    move_ant(t_ant **ant)
{
    (*ant)->pathptr = (*ant)->pathptr->next;
    if ((*ant)->pathptr == NULL)
        del_ant(ant);
}

void print_ant(t_ant ant)
{
    printf("L%d-%s", ant.name, (char *)ant.pathptr->content);
}