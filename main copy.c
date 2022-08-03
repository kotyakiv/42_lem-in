/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/08/03 00:43:26 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	main(int argc, char **argv)
{
	t_farm	farm;

	ft_bzero(&farm, sizeof(farm));
	if (argc != 1 && argv)
		error(&farm);
	//read_input(&farm);
	farm.num_ants = 25;
	/* algo */
	/**********************************/

	
	t_list	**paths;
	int i = 0;
	char c = 'a';
	char	str[50];

	ft_bzero((void *)str, 50);
	paths = (t_list **)ft_memalloc(sizeof(t_list *) * 5);
	ft_bzero(paths, sizeof(t_list *) * 5);
	{
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		++i;
	}
	{
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		++i;
	}
	{
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		++i;
	}
	{
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		str[ft_strlen(str)] = c++;
		ft_lstappend(&paths[i], ft_lstnew(str, ft_strlen(str) + 1));
		++i;
	}
	for (int a = 0; a < 4;a++)
	{
		for (t_list *iter = paths[a]; iter; iter = iter->next)
			printf("%s ", (char *)(iter->content));
		printf("\n");
	}

	send_ants(farm.num_ants, paths);
	/**********************************/
//	print_farm(farm);
	free_farm(&farm);
	return (0);
}
