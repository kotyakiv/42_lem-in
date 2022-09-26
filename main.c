/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/09/25 19:59:05 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

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
		err_nolines(farm, "More than one argument");
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

	init_farm(&farm);
	if (read_options(&farm, argc, argv))
		err_nolines(&farm, "Wrong arguments");
	read_input(&farm);
	print_farm(farm);
	farm.option1 = get_paths(&farm, 1);
	if (farm.option1 == NULL)
		err_nolines(&farm, "No path to end");
	farm.option2 = get_paths(&farm, 2);
	find_the_best_paths_and_send_ants(&farm);
	free_farm(&farm);
	//system("leaks lem-in >> leaks.txt"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
