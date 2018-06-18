# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 10:11:17 by vtarasiu          #+#    #+#              #
#    Updated: 2018/06/16 18:45:30 by vtarasiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
EXEC = printf_test
LIB_DIR = ./libft
LIB_NAME = libft.a
LIB_FILES = ft_bzero.c ft_memcpy.c ft_memccpy.c ft_strcpy.c ft_strcat.c \
            ft_strchr.c ft_strrchr.c ft_strcmp.c ft_isprint.c ft_strncpy.c \
            ft_strncat.c ft_isascii.c ft_strncmp.c ft_memchr.c ft_strnstr.c \
            ft_atoi.c ft_memcmp.c ft_strlen.c ft_strlcat.c ft_memalloc.c \
            ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_strstr.c \
            ft_strmap.c ft_striter.c ft_striteri.c ft_strmapi.c ft_strequ.c \
            ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_putchar.c \
            ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
            ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strsplit.c \
            ft_memmove.c ft_strdup.c ft_tolower.c ft_toupper.c ft_isdigit.c \
            ft_isalnum.c ft_isalpha.c ft_itoa.c ft_memset.c ft_lstnew.c \
            ft_lstdelone.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstdel.c \
            ft_wchar_strlen.c ft_nbrlen.c ft_utf_strlen.c

PRINTF_SRC = stringf.c integerf.c nbr_util.c ft_printf.c generic_functions.c \
            generic_functions2.c util.c unicode.c parsing.c evals.c evals2.c \
            variations.c

LIB_SRC = $(addprefix $(LIB_DIR)/, $(LIB_FILES))
OBJ = $(LIB_FILES:.c=.o) $(PRINTF_SRC:.c=.o)

$(NAME):
	gcc -c $(LIB_SRC) $(PRINTF_SRC) -std=c99 -Wall -Wextra -Werror \
    && ar rc $(NAME) $(OBJ)
	make clean

all: $(NAME)

exec: all
	gcc -o $(EXEC) main.c libftprintf.a

cleanlib:
	make -C ./libft clean

clean: cleanlib
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

check:
	gcc -c ft_*.c -std=c99 -Wall -Wextra -Werror && norminette ft_*.c *.h

love:
	@echo "Not all."
