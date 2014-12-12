#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 10:38:16 by rdestreb          #+#    #+#              #
#    Updated: 2014/12/12 10:51:25 by rdestreb         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls
SRCDIR = ./
HEADDIR = ./
HEAD = ft_ls.h
HEADFILES = $(addprefix $(HEADDIR)/, $(HEAD))
SCRFILES = $(addprefix $(SRCDIR)/, $(SRC))
SRC =	main.c \
		option.c \
		read.c \
		get_data.c \
		print.c \
		list.c

OBJS = $(SCRFILES:.c=.o)
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
LDFLAGS = -L ./libft/ -lft
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C ./libft/

%.o: %.c $(HEADERFILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE) -C ./libft/ $@
	/bin/rm -f $(OBJS)

fclean: clean
	$(MAKE) -C ./libft/ $@
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
