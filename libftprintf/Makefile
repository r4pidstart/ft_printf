# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 02:46:38 by tjo               #+#    #+#              #
#    Updated: 2022/07/25 22:11:53 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf_main.c ft_printf_parse.c ft_printf_print.c ft_printf_utils.c ft_printf_write.c

all: $(NAME)

$(NAME): $(SRCS:.c=.o)
	ar rcs $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re:
	fclean
	all

.PHONY: bonus all clean fclean re