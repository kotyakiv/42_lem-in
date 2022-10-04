/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:05:24 by ykot              #+#    #+#             */
/*   Updated: 2022/10/03 13:30:33 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int equal_paths(t_list *first, t_list *second)
{
    while (first || second)
    {
        if (first == NULL && second != NULL)
            return (0);
        if (first != NULL && second == NULL)
            return (0);
        ft_printf("%s\n", (char *)first->content);
        ft_printf("%s\n", (char *)second->content);
        if (!ft_strequ((char *)first->content, (char *)second->content))
            return (0);
        first = first->next;
        second = second->next;       
    }
    return (1);
}

int new_path(t_list *path, t_list *all_paths)
{
    t_list *temp;

    while (all_paths)
    {   
        temp = (t_list *)all_paths->content;
        if (equal_paths(path, temp))
            return (0); 
        all_paths = all_paths->next;
    }
    return (1);
}

void    print_all_paths(t_list *all_paths)
{
    t_list *temp;
    
    while (all_paths)
    {
        temp = (t_list *)all_paths->content;
        while (temp)
        {
            ft_putstr((char *)(temp->content));
            ft_putstr(" > ");
            temp = temp->next;
        }
        ft_putstr("\n\n");
        all_paths = all_paths->next;
    }
    
}