/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:39 by ykot              #+#    #+#             */
/*   Updated: 2022/08/03 10:41:25 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void    print_queue(t_list **queue, int *size)
{
    for (int a = 0; a < *size;a++)
	{
		for (t_list *iter = queue[a]; iter; iter = iter->next)
			printf("%d ", ((t_ant *)(iter->content))->name);
		printf("\n");
	}
}

void    print_moving(t_list *moving_ants)
{
    while (moving_ants)
    {
        printf("%d ", ((t_ant *)moving_ants->content)->name);
        moving_ants = moving_ants->next;
    }
    printf("\n");
}

static void    ant_push(t_ant  *ant, t_list **queue)
{
    t_list  *new;

    new = ft_lstnew(ant, sizeof(t_ant));
    if (new == NULL)
        return ; //error
    ft_lstappend(queue, new);
}

static  int *get_numrooms(t_list **paths, int size)
{
    int     *rooms;
    int     i;
    
    rooms = (int *)ft_memalloc(sizeof(int) * size);
    i = 0;
    while (i < size)
    {
        rooms[i] = ft_lstsize(paths[i]);
        ++i;
    }
    return (rooms);
}

t_list  **make_queue(int num_ants, t_list **paths, int *size)
{
    t_list  **queue;
    int     *rooms;
    int     n_i;
    int     j;

    *size = ft_lstsize((t_list *)paths);
    queue = (t_list **)ft_memalloc(sizeof(t_list *) * *size);
    rooms = get_numrooms(paths, *size);
    n_i = 0;
    j = 0;
    while (++n_i <= num_ants)
    {
        if (rooms[j] + (int)ft_lstsize(queue[j]) > rooms[j + 1] && j + 1 != *size)
        {
            j++;
            ant_push(new_ant(n_i, queue[j]), &queue[j]);
        }
        else
        {
            j = 0;
            ant_push(new_ant(n_i, queue[j]), &queue[j]);
        }
    }
    return (queue);
}

static void del(void *content, size_t size)
{
    ft_memdel(&content);
    size++;
}

static void    move_all_ants(t_list **moving_ants)
{
    t_list  *iter;
    int     i;
    t_ant   *ant;
    
    i = 0;
    iter = *moving_ants;
    while (iter)
    {
        ant = (t_ant *)iter->content;
        print_ant(*ant);
        move_ant(&ant);
        if (ant == NULL)
        {
            iter = iter->next;
            ft_lstdelelem(moving_ants, i, del);
            continue ;
        }
        i++;
        iter = iter->next;
    }
}

static void   ant_pop(t_list ***queue, t_list **moving_ants, int *size)
{
    t_list  *elem;
  //  t_list  *prev;
    int i;
    
    i = 0;
    while (i < *size)
    {
        //prev = queue[i];
        elem = (*queue)[i];
        elem->next = NULL;
        ft_lstappend(moving_ants, elem);
        /*
        elem = ft_lstnew(iter->content, iter->content_size);
        
        iter = iter->next;
        */
        
        ft_lstdelelem(&queue[i][0], 0, del);
        
        if ((*queue)[i] == NULL)
        {
            ft_lstdelelem((t_list **)queue, i, del);
            *size -= 1;
        }
        print_queue(*queue, size);
        print_moving(*moving_ants);
        printf("------------------\n");
        i++;
    }
}

void    send_ants(int num_ants, t_list **paths)
{
    t_list  **queue;
    t_list  *moving_ants;
    int     size;
    
    moving_ants = NULL;
    size = 0;
    queue = make_queue(num_ants, paths, &size);
    
    print_queue(queue, &size);

    ant_pop(&queue, &moving_ants, &size);
    while (queue || moving_ants)
    {
        move_all_ants(&moving_ants);
        ant_pop(&queue, &moving_ants, &size);
    }
}
