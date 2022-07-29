# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 02:46:38 by tjo               #+#    #+#              #
#    Updated: 2022/07/30 02:11:46 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror

SRCS_MANDATORY = ft_printf_main.c ft_printf_parse.c ft_printf_print.c ft_printf_utils.c ft_printf_write.c
SRCS_BONUS = ft_printf_main_bonus.c ft_printf_parse_bonus.c ft_printf_print_bonus.c ft_printf_utils_bonus.c ft_printf_write_bonus.c

all: $(NAME)

$(NAME): $(SRCS_MANDATORY:.c=.o)
	ar rcs $(NAME) $^

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@

bonus:
	$(MAKE) SRCS_MANDATORY="$(SRCS_BONUS)" all

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean 
	$(MAKE) all

.PHONY: bonus all clean fclean re