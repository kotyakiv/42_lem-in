/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:39 by ykot              #+#    #+#             */
/*   Updated: 2022/08/04 22:22:55 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
/*
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
*/
static int  *get_numrooms(t_list **paths, int size)
{
    int     *rooms;
    int     i;
    
    rooms = (int *)ft_memalloc((size_t)(sizeof(int) * size));
    if (rooms == NULL)
        return (NULL);
    i = 0;
    while (i < size)
    {
        rooms[i] = ft_lstsize(paths[i]);
        ++i;
    }
    return (rooms);
}

t_list  **make_queue(int num_ants, t_list **paths, int size)
{
    t_list  **queue;
    int     *rooms;
    int     j;

    queue = (t_list **)ft_memalloc(sizeof(t_list *) * size);
    rooms = get_numrooms(paths, size);
    j = 0;
    while (num_ants--)
    {
        if (j + 1 != size && rooms[j] + (int)(ft_lstsize(queue[j])) > rooms[j + 1])
        {
            j++;
            ant_push(paths[j], &queue[j]);
        }
        else
        {
            j = 0;
            ant_push(paths[j], &queue[j]);
        }
    }
    free(rooms);
    return (queue);
}

static void    del(void  *content, size_t size)
{
    free(content);
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
        if (iter->next == NULL)
            printf("\n");
        else
            printf(" ");
        move_ant(ant);
        if (ant->pathptr == NULL)
        {
            iter = iter->next;
            ft_lstdelelem(moving_ants, i, del);
            continue ;
        }
        i++;
        iter = iter->next;
    }
}

void    send_ants(int num_ants, t_list **paths)
{
    t_list  **queue;
    t_list  *moving_ants;
    int     size;
    int     cur_ant_num;
    
    moving_ants = NULL;
    cur_ant_num = 1;
    size = ft_lstsize((t_list *)paths);
    queue = make_queue(num_ants, paths, size);
    ant_pop(&queue, &moving_ants, size, &cur_ant_num);
    while (moving_ants)
    {
        move_all_ants(&moving_ants);
        ant_pop(&queue, &moving_ants, size, &cur_ant_num);
    }
    free(queue);
    while (size)
    {
        ft_lstdel(&(paths[--size]), del);
        free(paths[size]);
    }
    free(paths);
}
