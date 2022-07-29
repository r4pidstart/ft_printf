all:
	clang -Wall -Wextra -Werror -g3 -ggdb \
	libftprintf/ft_printf_main.c libftprintf/ft_printf_parse.c libftprintf/ft_printf_print.c libftprintf/ft_printf_utils.c libftprintf/ft_printf_write.c test.c \
	-o test