/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/09/21 11:00:54 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

/*static size_t total_path_size(t_list **path, size_t size)
{
	size_t i;
	size_t result;

	i = 0;
	result = 0;
	while (i < size)
	{
		result += ft_lstsize(path[i]);
		i++;
	}
	return (result);
}*/

static void null_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void	free_set_i(t_list **set_i, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (set_i[i])
		{
			ft_lstdel(&set_i[i], null_fn);
		}
		i++;
	}
	free(set_i);
}

void	free_paths(t_list **alst)
{
	t_list	*curr;
	t_list	*next;

	if (!alst || !*alst)
		return ;
	curr = *alst;
	int i = 0;
	while (curr)
	{
		next = curr->next;
		free_set_i(curr->content, i + 1);
		free(curr);
		curr = next;
		i++;
	}
	*alst = NULL;
}

static void init_farm(t_farm *farm)
{
	ft_bzero(farm, sizeof(*farm));
	farm->hashmap = ft_memalloc(HASH * sizeof(t_list *));
}

static void print_help(t_farm *farm)
{
	ft_putstr("Usage: ./lem-in [OPTION] < valid map\n\n");
	ft_putstr("\t-h\thelp\n");
	ft_putstr("\t-p\tprint sets of possible paths and number of lines to print\n");
	ft_putstr("\t-v\trun visualisator\n");
	free_farm(farm);
	exit(0);
}

static int	read_options(t_farm *farm, int argc, char **argv)
{
	if (argc > 2)
		error(farm, "More than one argument");
	if (ft_strequ(argv[1], "-v"))
		farm->flag.v = 1;
	else if (ft_strequ(argv[1], "-h"))
		print_help(farm);
	else if (ft_strequ(argv[1], "-p"))
		farm->flag.p = 1;
	else if (argc != 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_farm	farm;
	t_list *option1;

	init_farm(&farm);
	if (read_options(&farm, argc, argv))
		error(&farm, "Wrong arguments");
	read_input(&farm);
	print_farm(farm);
	option1 = get_paths(&farm, 2); // some maps are still better with option1

	if (option1 == NULL)
		error(&farm, "No path to end");
	print_path_sets(option1);
	find_the_best_paths_and_send_ants(option1, &farm);
	free_farm(&farm);
	free_paths(&option1);
	//system("leaks lem-in >> leaks.txt"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
