# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marde-vr <marde-vr@42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/04 08:03:00 by tomoron           #+#    #+#              #
#    Updated: 2025/02/14 17:48:08 by tomoron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc

SRCS =	ft_protected_atoi.c\
		ft_convert.c\
		ft_isdigit.c\
		ft_parse_arg.c\
		ft_print_hex_ptr.c\
		ft_print_int.c\
		ft_print_unsigned_int.c\
		ft_printf.c\
		ft_putchar.c\
		ft_putstr.c\
		ft_strlen.c\
		ft_write_str_part.c\
		ft_printf_fd.c\
		ft_printf_fd_utils.c
		
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -Wno-unused-result

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

bonus: all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: bonus clean all re fclean
