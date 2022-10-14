/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:14:57 by ykot              #+#    #+#             */
/*   Updated: 2022/10/07 17:18:14 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	seek_more_newline(char **remaining, char **line)
{
	char	*p_newline;
	char	*prev;

	p_newline = ft_strchr(*remaining, '\n');
	if (p_newline)
	{
		*p_newline = '\0';
		prev = *remaining;
		*line = ft_strdup(*remaining);
		*remaining = ft_strdup(p_newline + 1);
		ft_strdel(&prev);
		return (1);
	}
	else
	{
		*line = ft_strdup(*remaining);
		ft_strdel(remaining);
	}
	return (0);
}

static void	update_line(char **line, char *buff)
{
	char	*oldline;

	oldline = *line;
	*line = ft_strjoin(*line, buff);
	ft_strdel(&oldline);
}

static int	get_newline(char **line, char *buff, char **left, const int fd)
{
	char	*newline;

	newline = ft_strchr(buff, '\n');
	if (newline)
	{
		*newline = '\0';
		left[fd] = ft_strdup(newline + 1);
		if (!left[fd])
			return (-1);
		update_line(line, buff);
		if (!line)
			return (-1);
		return (1);
	}
	update_line(line, buff);
	if (!line)
		return (-1);
	return (0);
}

static int	read_line(const int fd, char **left, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			read_bytes;
	int			got;

	while (1)
	{
		read_bytes = read(fd, buff, BUFF_SIZE);
		if (read_bytes == 0 || read_bytes == -1)
		{
			if (ft_strlen(*line) > 0)
				return (1);
			ft_strdel(&left[fd]);
			ft_strdel(line);
			return (read_bytes);
		}
		buff[read_bytes] = '\0';
		got = get_newline(line, buff, left, fd);
		if (got != 0)
			return (got);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*left[FD_MAX];

	if (fd < 0 || line == NULL || fd >= FD_MAX)
		return (-1);
	if (left[fd] != NULL)
	{
		if (seek_more_newline(&left[fd], line) == 1)
			return (1);
	}
	else
		*line = ft_strnew(1);
	return (read_line(fd, left, line));
}
