# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 12:43:30 by jtsizik           #+#    #+#              #
#    Updated: 2022/11/28 15:59:05 by jtsizik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo

SRCS =	philo.c \
		init.c \
		routine.c \
		time_utils.c \
		utils.c \
		error.c

OBJS = $(SRCS:.c=.o)

$(NAME):
	cc -Wall -Wextra -Werror -c $(SRCS)
	cc -Wall -Wextra -Werror $(OBJS) -g -o $(NAME) -I philo.h

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all