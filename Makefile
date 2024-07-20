# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andtan <andtan@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 10:48:43 by andtan            #+#    #+#              #
#    Updated: 2024/07/13 15:46:30 by andtan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
BONUS_NAME = get_next_line_bonus.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42
SRCS = get_next_line.c get_next_line_utils.c
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS := $(SRCS:.c=.o)
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
