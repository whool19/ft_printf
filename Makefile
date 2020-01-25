# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jslave <jslave@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 21:32:49 by jslave            #+#    #+#              #
#    Updated: 2019/11/19 17:38:22 by jslave           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a

LIBFT = libft

LIBFT_INCLUDES = libft/includes

INCLUDES = inc/

FLAGS = -Wall -Wextra -Werror

SRC = src/chars-int-percent.c src/precision.c src/floats.c \
src/ft_itoa_new.c src/ft_printf.c src/ints.c src/parsing.c \
src/pnt-oct-hex.c src/print_str_char.c src/utils.c \
src/ints_utils.c src/oct_test.c src/hex.c

OUT = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OUT)
	make -C $(LIBFT)
	cp libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OUT)
	ranlib $(NAME)
%.o: %.c
	gcc -g $(FLAGS) -I $(LIBFT_INCLUDES) -I $(INCLUDES) -o $@ -c $<

clean:
	/bin/rm -f $(OUT)
	make -C $(LIBFT) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

test: libftprintf.a main_test.c
	gcc libftprintf.a main_test.c

cake: all main_test.c
	make re
	make test
	make clean
