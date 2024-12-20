# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 16:41:30 by tbabou            #+#    #+#              #
#    Updated: 2024/12/13 03:59:12 by tbabou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = src/main.c \
	  src/utilities.c \
	  src/cleanup.c \
	  src/parseinput.c \
	  src/routine.c \
	  src/simulation.c \
	  src/init.c \
	  src/eat.c

OBJS = $(SRC:.c=.o)

.SECONDARY: $(OBJS)

INCLUDES = includes/
CFLAGS = -Wall -Werror -Wextra -g3

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
