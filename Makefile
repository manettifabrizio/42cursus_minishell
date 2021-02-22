# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/26 17:06:32 by fmanetti          #+#    #+#              #
#    Updated: 2021/02/22 23:06:45 by fmanetti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minish

FILES		=	minishell.c							\
				path.c								\
				signals_term.c						\
				read/read.c							\
				read/str_print_and_handle.c			\
				keys/keys.c							\
				keys/control.c						\
				builtins/builtins.c					\
				builtins/ft_echo.c					\
				builtins/ft_export.c				\
				builtins/ft_unset.c					\
				parse/parse.c						\
				parse/lists/ms_lstnew.c				\
				parse/lists/ms_lstlast.c			\
				parse/lists/ms_lstadd_back.c		\
				parse/lists/ms_list_sort.c			\
				parse/lists/ms_print_list.c			\
				parse/split/ms_split_exp.c			\
				parse/split/ms_split_var.c		

HFILES		=	minishell.h

LIB			=	libft.a

SOURCE		=	$(addprefix ./srcs/, $(FILES))
HEADERS		=	$(addprefix ./include/, $(HFILES))
INCLUDE		=	$(addprefix ./include/libft/, $(LIB))

OBJ			=	$(SOURCE:%.c=%.o)

CC			= 	clang

CFLAGS		= 	-I include/ -Wall -Wextra -Werror
FSANITIZE	= 	-g3 -O0 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@printf "[ $(NAME) ] Compiling...\r"
	@($(CC) -o $(NAME) $(SOURCE) $(INCLUDE) $(CFLAGS) $(FSANITIZE))
	@printf "[ $(NAME) ] Compiled \033[0;32mSuccessfully\n\033[0m"

lib:
	@make re bonus -C include/libft
	@make clean -C include/libft

key:
	@gcc -o key keycode.c $(CFLAGS)
	@./key
	@rm key

clean:
	@/bin/rm -f $(OBJ)
	@printf "Object files \033[0;31mremoved\n\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)*
	@/bin/rm -rf .vscode
	@printf "[ $(NAME) ] \033[0;31mremoved\n\033[0m"

re: fclean all

.PHONY: all clean fclean re

.SILENT: