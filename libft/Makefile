# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 23:20:01 by ykot              #+#    #+#              #
#    Updated: 2022/10/06 17:01:38 by bkandemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 		ft_atoi.c \
			ft_lstdelone.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strlcat.c \
			ft_strrchr.c \
			ft_bzero.c \
			ft_lstiter.c \
			ft_putchar.c \
			ft_strclr.c \
			ft_strlen.c \
			ft_strsplit.c \
			ft_isalnum.c \
			ft_lstnew.c \
			ft_putchar_fd.c \
			ft_strcmp.c \
			ft_strmap.c \
			ft_strstr.c \
			ft_isalpha.c \
			ft_memalloc.c \
			ft_putendl.c \
			ft_strcpy.c \
			ft_strmapi.c \
			ft_strsub.c \
			ft_isascii.c \
			ft_memccpy.c \
			ft_putendl_fd.c \
			ft_strdel.c \
			ft_strncat.c \
			ft_strtrim.c \
			ft_isdigit.c \
			ft_memchr.c \
			ft_putnbr.c \
			ft_strdup.c \
			ft_strncmp.c \
			ft_tolower.c \
			ft_isprint.c \
			ft_memcmp.c \
			ft_putnbr_fd.c \
			ft_strequ.c \
			ft_strncpy.c \
			ft_toupper.c \
			ft_itoa.c \
			ft_memcpy.c \
			ft_putstr.c \
			ft_striter.c \
			ft_strnequ.c \
			ft_lstadd.c \
			ft_memdel.c \
			ft_putstr_fd.c \
			ft_striteri.c \
			ft_strnew.c \
			ft_lstdel.c \
			ft_memmove.c \
			ft_strcat.c \
			ft_strjoin.c \
			ft_strnstr.c \
			ft_lstmap.c \
			ft_lstappend.c \
			ft_lstelem.c \
			ft_lstsize.c \
			ft_lstdelelem.c \
			ft_lstaddelem.c \
			ft_strrev.c \
			ft_strtoup.c \
			ft_putllnbr.c \
			ft_pow.c \
			ft_numdig.c \
			ft_numundig.c \
			ft_bigger.c \
			ft_demtobase.c \
			get_next_line.c \
			ft_dlstdel.c \
			ft_dlstdelone.c \
			ft_dlstnew.c \
			ft_dynlstadd.c \
			ft_dynlstappend.c \
			ft_dynlstdelelem.c \
			ft_dynlstelem.c \
			ft_dlstnew_pointer.c\
			ft_lstnew_pointer.c\
			ft_char_count.c

SRC_PF = 	ft_printf.c \
			print_conversion.c \
			conversion_specification.c \
			print_decimal.c \
			sub_functions.c \
			print_flags.c \
			print_unsigned.c \
			checking.c \
			reading_option.c \
			width_precision.c \
			print_scp.c \
			print_float.c \
			print_float2.c \
			print_float3.c \
			rounding.c

OBJ = $(SRC:.c=.o)
OBJ_PF = $(SRC_PF:.c=.o)
NAME = libft.a
CFLAGS = -c -Wall -Werror -Wextra
FT_PRINTF_PATH = ft_printf/


all: $(NAME)

$(NAME):
	@gcc $(CFLAGS) $(SRC) $(addprefix $(FT_PRINTF_PATH), $(SRC_PF))
	@ar rc $(NAME) $(OBJ) $(OBJ_PF)

clean:
	@rm -f $(OBJ) $(OBJ_PF)

fclean: clean
	@rm -f $(NAME)

re: fclean all
