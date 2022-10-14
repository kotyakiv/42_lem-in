/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:25:04 by ykot              #+#    #+#             */
/*   Updated: 2022/10/09 23:04:22 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	is_comment(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

void	save_input(t_farm *farm, char **line)
{
	t_dblist	*tempptr;
	char		*str;

	str = ft_strdup(*line);
	if (str == NULL)
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	tempptr = ft_dblstnew_pointer(str);
	if (tempptr == NULL)
	{
		free(str);
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	}
	ft_dynlstappend(&(farm->input_lines), tempptr);
	farm->flag.read_lines++;
}

static int	check_gnl(t_farm *farm, int gnl, char **line)
{
	if (gnl == -1)
		error(farm, ERR_READ);
	if (gnl == 0 && farm->start && farm->end && farm->flag.is_links == 0)
	{
		ft_strdel(line);
		farm->flag.read_lines++;
		error(farm, ERR_NO_LINK);
	}
	if (gnl == 0 && farm->start && farm->end)
	{
		ft_strdel(line);
		return (1);
	}
	if (gnl == 0)
	{
		farm->flag.no_errlines = 1;
		if (farm->start == NULL && farm->end == NULL)
			error(farm, ERR_START_END);
		if (farm->start == NULL)
			error(farm, ERR_START);
		if (farm->end == NULL)
			error(farm, ERR_END);
	}
	return (0);
}

int	enough_data(t_farm *farm, char **line)
{
	if (farm->start && farm->end && farm->rooms.head && farm->flag.is_links)
	{
		ft_dynlstdelelem(&farm->input_lines,
			farm->input_lines.size - 1, del_dblfn);
		ft_strdel(line);
		return (1);
	}
	else if (farm->flag.is_links == 0)
		error(farm, ERR_NO_LINK);
	else
	{
		farm->flag.no_errlines = 1;
		error(farm, ERR_MAP);
	}
	return (0);
}

void	read_input(t_farm *farm)
{
	char	*line;
	int		gnl;

	line = NULL;
	get_ant_num(farm, &line);
	while (TRUE)
	{
		ft_strdel(&line);
		gnl = get_next_line(0, &line);
		if (check_gnl(farm, gnl, &line))
			return ;
		if (ft_strlen(line) == 0)
			err_empty_line(farm);
		save_input(farm, &line);
		if (is_comment(line))
			continue ;
		if (is_command(farm, &line))
			continue ;
		if (get_rooms_links(farm, line))
			continue ;
		if (enough_data(farm, &line))
			return ;
	}
	ft_strdel(&line);
}
