# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soel-kar <soel-kar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 21:50:52 by soel-kar          #+#    #+#              #
#    Updated: 2021/09/23 22:34:07 by soel-kar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

RM = rm -rf

NAME = pipex

SDIR = ./srcs/

SRC =	pipex.c				\
		other.c		\
		ft_split.c			\
		libft.c				\
		

IDIR = ./includes/

CFLAGS = -Wall -Wextra -Werror -g


SRCS =	$(addprefix $(SDIR), $(SRC)) ./srcs/pipex.c

OBJDIR = ./objs
OBJS =	$(OBJDIR)/*.o

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -I $(IDIR) $(OBJS) -o $(NAME)

$(OBJS):	$(SRCS)
			@$(CC) -c $(CFLAGS) $(SRCS)
			rm -rf ./objs; mkdir ./objs
			mv *.o $(OBJDIR)

clean:
	$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all, clean, fclean, re
