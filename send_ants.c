/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:39 by ykot              #+#    #+#             */
/*   Updated: 2022/09/21 09:15:47 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/* Functions to see what we have in the queue and moving ants*/

/*
void    print_queue(t_list **queue, int *size)
{
    for (int a = 0; a < *size;a++)
	{
		for (t_list *iter = queue[a]; iter; iter = iter->next)
			printf("%d ", ((t_ant *)(iter->content))->name);
		printf("\n");
	}
}

void    print_moving(t_list *moving_ants)
{
    while (moving_ants)
    {
        printf("%d ", ((t_ant *)moving_ants->content)->name);
        moving_ants = moving_ants->next;
    }
    printf("\n");
}
*/
int	*get_numrooms(t_list **paths, int size)
{
	int	*rooms;
	int	i;
	
	rooms = (int *)ft_memalloc((size_t)(sizeof(int) * size));
	if (rooms == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		rooms[i] = ft_lstsize(paths[i]);
		if (rooms[i] == 0)
			return (NULL);
		++i;
	}
	return (rooms);
}

t_list	**make_queue(int num_ants, t_list **paths, int size)
{
	t_list	**queue;
	int		*rooms;
	int		j;

	queue = (t_list **)ft_memalloc(sizeof(t_list *) * size);
	rooms = get_numrooms(paths, size);
	j = 0;
	while (num_ants--)
	{
		if (j + 1 != size && rooms[j] + (int)(ft_lstsize(queue[j])) > rooms[j + 1])
		{
			j++;
			ant_push(paths[j], &queue[j]);
		}
		else
		{
			j = 0;
			ant_push(paths[j], &queue[j]);
		}
	}
	free(rooms);
	return (queue);
}

static void	del(void  *content, size_t size)
{
	free(content);
	size++;
}

static void	move_all_ants(t_list **moving_ants)
{
	t_list	*iter;
	int		i;
	t_ant	*ant;
	
	i = 0;
	iter = *moving_ants;
	while (iter)
	{
		ant = (t_ant *)iter->content;
		print_ant(*ant);
		if (iter->next == NULL)
			printf("\n");
		else
			printf(" ");
		move_ant(ant);
		if (ant->pathptr == NULL)
		{
			iter = iter->next;
			ft_lstdelelem(moving_ants, i, del);
			continue ;
		}
		i++;
		iter = iter->next;
	}
}

void	send_ants(int num_ants, t_list **paths, int size)
{
	t_list	**queue;
	t_list	*moving_ants;
	int		cur_ant_num;
	
	moving_ants = NULL;
	cur_ant_num = 1;
	//print_paths(paths, size);
	queue = make_queue(num_ants, paths, size);
	//printf ("NO\n");
	ant_pop(&queue, &moving_ants, size, &cur_ant_num);
	while (moving_ants)
	{
		move_all_ants(&moving_ants);
		ant_pop(&queue, &moving_ants, size, &cur_ant_num);
	}
	free(queue);
}

int count_printed_lines(int num_ants, int *queue, int size)
{
	int	i;

	i = 0;	
	while (num_ants--)
	{
		if (i + 1 != size && queue[i] > queue[i + 1])
		{
			i++;
			queue[i]++;
		}
		else
		{
			i = 0;
			queue[i]++;
		}
	}
	/*
	** print length of path + ants in queue
	for (int j = 0; j < size; j++)
		ft_printf("%d ", queue[j]);
	ft_printf("\n");*/
	return (queue[0]);
}

static void	print_flag_p(t_list **the_set, int num_lines, int i)
{
	printf("set %d:\n", i);
	printf("Number of lines to print: %d\n", num_lines - 1);
	print_paths(the_set, i + 1);
}

static int	the_best_path(t_list *sets, int num_ants, int flag_p)
{
	t_list **the_set;
	t_list *curr;
	int	min_lines;
	int	best_path;
	int	*queue;
	int	num_lines;
	int	i;
	
	i = 0;
	curr = sets;
	min_lines = INT_MAX;
	while (curr)
	{
		the_set = curr->content;
		queue = get_numrooms(the_set, i + 1);
		if (queue == NULL)
			break;
		num_lines = count_printed_lines(num_ants, queue, i + 1);
		if (flag_p)
			print_flag_p(the_set, num_lines, i);
		if (min_lines > num_lines)
		{
			min_lines = num_lines;
			best_path = i;
		}
		free(queue);
		i++;
		curr = curr->next;
	}
	return (best_path);
}

void	find_the_best_paths_and_send_ants(t_list *sets, t_farm *farm)
{
	int		best_set_num;
	int		i;
	t_list	**the_set;
	t_list	*curr;		

	best_set_num = the_best_path(sets, farm->num_ants, farm->flag.p);
	i = 0;
	curr = sets;
	while (i <= best_set_num)
	{
		the_set = curr->content;
		i++;
		curr = curr->next;
	}
	send_ants(farm->num_ants, the_set, best_set_num + 1);
}
