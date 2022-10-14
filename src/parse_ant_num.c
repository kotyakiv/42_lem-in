/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ant_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:39:46 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 12:15:59 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ant_num_checks(t_farm *farm, char **line, int *num)
{
	char	**str;

	str = ft_strsplit(*line, ' ');
	if (str == NULL)
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	if (str[0] && str[1] != NULL)
		error_free_split_line(farm, &str, line, ERR_ANT_CHAR);
	free_split(&str);
	if (check_int(*line) == 0)
		error_free_split_line(farm, NULL, line, ERR_ANT_NOT_INT);
	*num = ft_atoi(*line);
	if (*num <= 0)
		error_free_split_line(farm, NULL, line, ERR_ANT_NB);
}

void	get_ant_num(t_farm *farm, char **line)
{
	int	num;

	while (TRUE)
	{
		ft_strdel(line);
		if (get_next_line(0, line) != 1)
		{
			if (farm->input_lines.head == NULL)
				err_nolines(farm, ERR_INPUT);
			else
				err_empty_line(farm);
		}
		save_input(farm, line);
		if (ft_strlen(*line) == 0)
			err_empty_line(farm);
		if (is_comment(*line))
			continue ;
		ant_num_checks(farm, line, &num);
		farm->num_ants = num;
		return ;
	}
}
