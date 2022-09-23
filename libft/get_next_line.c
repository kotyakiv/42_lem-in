/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:14:57 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 13:09:32 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_newline(char **line, char **str, int *result)
{
	char	*newl;
	char	*temp;

	*result = 0;
	newl = ft_strchr(*str, '\n');
	if (newl)
	{
		temp = ft_strsub(*str, 0, (size_t)(newl - *str));
		if (!temp)
		{
			*result = -1;
			return ;
		}
		*line = temp;
		temp = ft_strsub(*str, newl - *str + 1, \
			ft_strlen(*str) - ((size_t)(newl - *str) + 1));
		if (!temp)
		{
			*result = -1;
			return ;
		}
		ft_strdel(&(*str));
		*str = temp;
		*result = 1;
	}
}

static int	ft_alloc_buf(char **str, char **buf)
{
	char	*temp;

	if (*str)
	{
		temp = ft_strjoin(*str, *buf);
		if (!temp)
			return (-1);
		ft_strdel(&(*str));
		*str = temp;
		return (0);
	}
	else
	{
		*str = ft_strdup(*buf);
		if (!*str)
			return (-1);
		return (0);
	}
}

static void	ft_clr_and_read_buf(int fd, int *ret, char **buf)
{
	ft_strclr(*buf);
	*ret = read(fd, *buf, BUFF_SIZE);
}

static int	ft_ret(int fd, char **str, char **line, int *result)
{
	char	*buf;
	int		ret;

	buf = ft_strnew(BUFF_SIZE);
	if (!buf)
		return (-1);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret == -1)
		return (-1);
	while (ret)
	{
		if (ft_alloc_buf(str, &buf) == -1)
			return (-1);
		ft_newline(line, str, result);
		if (*result)
		{
			ft_strdel(&buf);
			return (*result);
		}
		ft_clr_and_read_buf(fd, &ret, &buf);
		if (ret == -1)
			return (-1);
	}
	ft_strdel(&buf);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static char	*str[MAX_FD];
	int			result;

	if (fd < 0 || fd > MAX_FD || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (str[fd])
	{	
		ft_newline(line, &(str[fd]), &result);
		if (result)
			return (result);
	}
	result = ft_ret(fd, &(str[fd]), line, &result);
	if (result)
		return (result);
	if (str[fd] && ft_strlen(str[fd]))
	{
		*line = str[fd];
		str[fd] = NULL;
		return (1);
	}
	return (0);
}
