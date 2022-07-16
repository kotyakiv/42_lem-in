/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:05:24 by ykot              #+#    #+#             */
/*   Updated: 2022/07/16 17:09:45 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void    print_farm(t_farm farm)
{
    t_list *temp;
    
    printf("%d\n", farm.num_ants);
    ft_putendl("##start");
    printf("%s %d %d\n", farm.start.name, farm.start.coord.x, farm.start.coord.y);
    ft_putendl("##end");
    printf("%s %d %d\n", farm.end.name, farm.end.coord.x, farm.end.coord.y);
    temp = farm.rooms;
    while (temp)
    {
        printf("%s %d %d\n", ((t_room *)temp->content)->name, \
        ((t_room *)temp->content)->coord.x, ((t_room *)temp->content)->coord.y);
        temp = temp->next;
    }
    temp = farm.links;
    while (temp)
    {
        ft_putendl((char *)temp->content);
        temp = temp->next;
    }
    ft_putendl("");
}
