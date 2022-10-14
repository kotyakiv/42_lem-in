/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/10/14 13:39:45 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_farm(t_farm *farm)
{
	ft_bzero(farm, sizeof(*farm));
	farm->option1 = NULL;
	farm->option2 = NULL;
	farm->hashmap = (t_list **)ft_memalloc(HASH * sizeof(t_list *));
	if (farm->hashmap == NULL)
		err_nolines(NULL, ERR_MEM_ALLOC);
}

static void	print_help(t_farm *farm)
{
	ft_putstr(USAGE);
	ft_putstr(HELP);
	ft_putstr(PRINT);
	ft_putstr(VISUAL);
	ft_putstr(VIS_USAGE);
	ft_putstr(COORD);
	ft_putstr(VIS_SLOW);
	ft_putstr(VIS_FAST);
	ft_putstr(VIS_BIG_MAP);
	ft_putstr(VIS_INFO);
	free_farm(farm);
	exit(0);
}

static int	read_options(t_farm *farm, int argc, char **argv)
{
	if (argc > 2)
		err_nolines(farm, ERR_MLTP_ARGS);
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
		err_nolines(&farm, ERR_ARGS);
	read_input(&farm);
	farm.option1 = get_paths(&farm, 1);
	if (farm.option1 == NULL)
		err_nolines(&farm, ERR_NO_PATH);
	farm.option2 = get_paths(&farm, 2);
	find_the_best_paths_and_send_ants(&farm);
	free_farm(&farm);
	return (0);
}
