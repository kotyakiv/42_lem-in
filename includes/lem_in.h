/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:20:47 by ykot              #+#    #+#             */
/*   Updated: 2022/10/21 13:21:58 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"

# define HASH 1109
# define INT_MAX 2147483647

/* error messages */
# define ERR_MEM_ALLOC "Memory allocation"
# define ERR_INPUT "File is empty or no input"
# define ERR_ANT_NOT_INT "The number of ants is not an integer"
# define ERR_ANT_NB "The number of ants less or equal to zero"
# define ERR_ANT_CHAR "Characters after the number of ants"
# define ERR_DBL_ANT "Double ant number"
# define ERR_ROOM "No rooms"
# define ERR_DBL_ROOM "Duplicate room name"
# define ERR_ROOM_L "Room begins with L"
# define ERR_NO_LINK "No links"
# define ERR_MAP "Invalid map"
# define ERR_EMP_LINE "Empty line"
# define ERR_MLTP_ARGS "More than one argument"
# define ERR_ARGS "Wrong arguments"
# define ERR_NO_PATH "No path to end"
# define ERR_COORD_INT "Coordinates are not integers"
# define ERR_READ "Fail to read a line"
# define ERR_START "No start"
# define ERR_END "No end"
# define ERR_START_END "No start and end"
# define ERR_LINK "Wrong link"
# define ERR_LINK_SAME "Same room in the link"
# define ERR_ROOM_AFT_LINK "Room after link"
# define ERR_LINK_DASH "Excess dash in the link"
# define ERR_AFT_COMMAND "No room after command"
# define ERR_EXT_START "More than one start"
# define ERR_EXT_END "More than one end"
# define ERR_SPACE "Invalid space count in the room line"

/* usage */
# define USAGE "Usage: ./lem-in [OPTION] < valid map\n\n"
# define HELP " -h\thelp\n"
# define PRINT " -p\tprint sets of possible paths and number of lines to print\n"
# define VISUAL " -v\tused with visualizer\n"
# define VIS_USAGE " \nVisualizer usage: \
./lem-in -v < valid map | python3 visualizer.py [OPTION]\n\n"
# define COORD " --coord\tto use coordinates, random nodes position by default\n"
# define VIS_SLOW " --slow\t\tslow animation of moving ants\n"
# define VIS_FAST " --fast\t\tfast animation of moving ants\n\n"
# define VIS_BIG_MAP " --big\tno labels and small size of nodes"
# define VIS_INFO "Visualizer uses networkx, matplotlib, numpy, scipy. \
Be sure that you have these packages installed\n\n \
pip3 install networkx matplotlib numpy scipy\n"

/* structs */
typedef struct s_coord
{
	int	x;
	int	y;
}		t_coord;

typedef struct s_node
{
	char			*name;
	struct s_node	*parent;
	t_dynlist		edges;
	struct s_room	*source;
}					t_node;

typedef struct s_room
{
	char	*name;
	t_coord	coord;
	t_node	*in;
	t_node	*out;
}			t_room;

typedef struct s_ant
{
	int		name;
	t_list	*pathptr;
}			t_ant;

typedef struct s_flag
{
	int	h;
	int	v;
	int	p;
	int	read_lines;
	int	no_errlines;
	int	rooms_done;
	int	is_links;
}		t_flag;

typedef struct s_index
{
	int	ind1;
	int	ind2;
}		t_index;

typedef struct s_farm
{
	int			num_ants;
	t_dynlist	rooms;
	t_dynlist	input_lines;
	t_room		*start;
	t_room		*end;
	t_list		**hashmap;
	t_flag		flag;
	t_index		index;
	t_list		**option1;
	t_list		**option2;
}				t_farm;

typedef struct s_edge
{
	t_node			*to;
	int				flow;
	struct s_edge	*reverse;
}				t_edge;

typedef struct s_hash
{
	char	*name;
	void	*ptr;
}			t_hash;

typedef struct s_pathsets
{
	t_list	**path_set;
	t_list	**prev_set;
	int		min_num_lines;
	int		option;
}			t_pathsets;

/* read_input */
int				is_comment(char *line);
void			save_input(t_farm *farm, char **line);
int				enough_data(t_farm *farm, char **line);
void			read_input(t_farm *farm);

/* checks */
int				check_int(const char *str);
int				is_char_in_str(char c, char *str);
int				has_single_dash(char *line);
int				has_double_space(char *line);
int				check_path_size(int *rooms, int size);

/* is_command */
int				is_command(t_farm *farm, char **line);

/* parse_ant_num */
void			get_ant_num(t_farm *farm, char **line);

/* get_rooms_links */
int				get_rooms_links(t_farm *farm, char *line);

/* parse_rooms */
char			**get_room_lines(char **line, t_farm *farm);
t_room			*create_room(char **str);
int				append_room(t_farm *farm, t_room *room);
t_node			*create_node(char **str, int is_in_or_out);

/* parse_links */
void			parse_links(t_farm *farm, char *line);
int				get_link(t_farm *farm, char **line);

/* hashmap */
unsigned long	hash(const char *s, unsigned long m);
void			*hashmap_get(t_list **hashmap, char *str);
int				hashmap_set(t_list **hashmap, char *str, void *ptr);
int				is_in(t_list **hashmap, char *str);
void			free_hashmap(t_list **hashmap);

/* make_adj_list */
t_edge			*create_edge(t_node *node);
int				append_edge(t_node *node, t_edge *edge);
int				make_adj_list(t_room *room1, t_room *room2);

/* get_paths */
t_list			**get_paths(t_farm *farm, int option);

/* get_paths_subfunctions */
int				when_to_stop(t_pathsets *pathsets, int index, t_farm *farm);
void			free_sets(t_pathsets *pathsets, int i);
t_list			**return_prev_set(t_farm *farm, t_pathsets *pathsets,
					int option, size_t i);
t_list			**return_curr_set(t_farm *farm, t_list **path_set,
					int option, size_t i);

/* bfs_utils */
int				q_push(t_list **queue, t_node *the_node);
t_node			*q_pop(t_list **queue);
int				free_and_exit_bfs(t_list **queue, t_list **visited, int exit);
void			free_err_hashmap(t_farm *farm, t_list **queue,
					t_list **visited);

/* bfs */
int				bfs(t_farm *farm, int flow);
int				bfs_reset(t_farm *farm);

/* update_residual_flow */
void			update_res_flow(t_farm *farm);

/* bfs_path */
int				bfs_path(t_farm *farm, int option);

/* update_fwd_flow */
void			update_fwd_flow(t_farm *farm, int flow);

/* mark_and_save_path */
void			reset_mark(t_farm *farm);
void			set_edge_flow(t_node *the_node, t_dblist *edges,
					t_edge *the_edge, int flow);
t_list			*mark_and_save_path(t_farm *farm, int flow);

/* print */
void			print_farm(t_farm farm);
void			print_paths(t_farm *farm, t_list **paths, size_t flow);

/* best_paths */
void			find_the_best_paths_and_send_ants(t_farm *farm);
int				*get_numrooms(t_list **paths, int size);
int				count_printed_lines(int num_ants, int *queue, int size);

/* ant_oop */
t_ant			*new_ant(t_list *pathptr);
void			move_ant(t_ant *ant);
void			print_ant(t_ant ant);
int				ant_push(t_list *path_ptr, t_list **queue);
void			ant_pop(t_list ***queue, t_list **moving_ants,
					int size, int *cur_ant_num);

/* send_ants */
t_list			**make_queue(t_farm *farm, t_list **paths, int size);
void			send_ants(t_farm *farm, t_list **paths, int size);

/* free_fn */
void			free_farm(t_farm *farm);
void			free_path_set(t_list **path_set, size_t size);
void			free_split(char ***str);

/* del_fn */
void			del_dblfn(void *content);
void			null_fn(void *content, size_t size);
void			del(void *content, size_t size);
void			del_rooms(void *content);

/* error_fn */
void			error(t_farm *farm, char *str);
void			error_free_split_line(t_farm *farm, char ***str,
					char **line, char *er_str);
void			err_nolines(t_farm *farm, char *str);
void			err_empty_line(t_farm *farm);

#endif
