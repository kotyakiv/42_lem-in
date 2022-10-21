# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 17:18:57 by bkandemi          #+#    #+#              #
#    Updated: 2022/10/21 13:22:54 by ykot             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

C_FILES =	ant_oop.c \
			best_paths.c \
			bfs.c \
			bfs_path.c \
			bfs_utils.c \
			checks.c \
			del_fn.c \
			error_fn.c \
			free_fn.c \
			get_paths.c \
			get_paths_subfunctions.c \
			get_rooms_links.c \
			hash.c \
			is_command.c \
			main.c \
			make_adj_list.c \
			mark_and_save_path.c \
			parse_ant_num.c \
			parse_links.c \
			parse_rooms.c \
			print.c \
			read_input.c \
			send_ants.c \
			update_fwd_flow.c \
			update_residual_flow.c
		
O_FILES = $(C_FILES:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra

SRC_PATH = src/

all : $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@$(CC) $(CFLAGS) -c $(addprefix $(SRC_PATH), $(C_FILES))  -I includes/
	@$(CC) $(CFLAGS) $(O_FILES) libft/libft.a -o $(NAME)

clean:
	@rm -f $(O_FILES)
	@make -C libft/ clean
 
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re:	fclean all
