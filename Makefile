# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomoron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 00:35:01 by tomoron           #+#    #+#              #
#    Updated: 2024/12/01 03:02:40 by tomoron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HOSTTYPE := $(shell uname -m)_$(shell uname -s)

NAME := libft_malloc_$(HOSTTYPE).so

CC = cc

SRCS_NAMES =	malloc.c \
				show_alloc_mem.c\
				free.c 

SRCS_DIR = srcs

OBJS_DIR := .objs

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAMES))

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_NAMES:.c=.o))

FLAGS = -Wall -Wextra -Werror -g

LFT = libft/libft.a

LFT_DIR = libft/

all: exec #libft_malloc.so

exec: $(OBJS_DIR) $(OBJS) $(LFT)
	$(CC) -o a.out $(FLAGS) main.c $(OBJS) $(LFT) 

libft_malloc.so: $(NAME)
	ln -sf $(NAME) libft_malloc.so

$(LFT):
	$(MAKE) -C $(LFT_DIR)

$(NAME): $(OBJS_DIR) $(OBJS) $(LFT)
	$(CC) -shared -o $(NAME) $(OBJS) $(LFT)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) -fPIC $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR) 
	make -C $(LFT_DIR) fclean

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so

re: fclean all


.PHONY: clean all re fclean
