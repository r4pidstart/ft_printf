all:
	clang -Wall -Wextra -Werror -g3 -ggdb \
	libftprintf/*.c test.c \
	-o test