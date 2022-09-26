# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 17:18:57 by bkandemi          #+#    #+#              #
#    Updated: 2022/09/24 19:58:12 by ykot             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

C_FILES = *.c
		
O_FILES = $(C_FILES:.c=.o)

CC = gcc -g

CC_DEBUG = gcc -g -fsanitize=address

CFLAGS = -Wall -Wextra

all : $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@$(CC) $(CFLAGS) -c $(C_FILES)
	@$(CC) $(CFLAGS) $(O_FILES) libft/libft.a -o $(NAME)

clean:
	@rm -f $(O_FILES)
	@make -C libft/ clean
 
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ clean

debug: fclean
	gcc -g -o lem-in *.c libft/*.c libft/ft_printf/*.c

re:	fclean
	@make -C libft/ fclean && make -C libft/
	@$(CC) $(CFLAGS) -c $(C_FILES)
	@$(CC) $(CFLAGS) $(O_FILES) libft/libft.a -o $(NAME)
	@rm -f $(O_FILES)
	@make -C libft/ clean
