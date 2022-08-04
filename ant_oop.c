/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_oop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:57:05 by ykot              #+#    #+#             */
/*   Updated: 2022/08/04 22:24:11 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_ant *new_ant(t_list *pathptr)
{
    t_ant   *new;

    new = (t_ant *)ft_memalloc(sizeof(t_ant));
    if (new == NULL)
        return (NULL);
    new->pathptr = pathptr;
    return(new);
}

void    move_ant(t_ant *ant)
{
    ant->pathptr = ant->pathptr->next;
}

void print_ant(t_ant ant)
{
    printf("L%d-%s", ant.name, (char *)ant.pathptr->content);
}

void    ant_push(t_list *path_ptr, t_list **queue)
{
    t_list  *new;
    t_ant   *ant;

    ant = new_ant(path_ptr);
    if (ant == NULL)
        return ; //error
    new = ft_lstnew(ant, sizeof(t_ant));
    free(ant);
    if (new == NULL)
        return ; //error
    ft_lstappend(queue, new);
}

void   ant_pop(t_list ***queue, t_list **moving_ants, int size, int *cur_ant_num)
{
    t_list  *elem;
    int i;
    
    i = 0;
    while (i < size)
    {
        if ((*queue)[i])
        {
            elem = (*queue)[i];
            (*queue)[i] = (*queue)[i]->next;
            elem->next = NULL;
            ((t_ant *)(elem->content))->name = (*cur_ant_num)++ ;
            ft_lstappend(moving_ants, elem);
        }
        i++;
    }
}
