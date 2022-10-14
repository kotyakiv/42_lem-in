/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:00:53 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/06 17:01:03 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_char_count(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			count++;
		i++;
	}
	return (count);
}
