# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/26 17:06:32 by fmanetti          #+#    #+#              #
#    Updated: 2021/02/11 09:44:43 by fmanetti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minish

FILES		=	minishell.c							\
				path.c								\
				builtins/builtins.c					\
				builtins/ft_echo.c					\
				builtins/ft_export.c				\
				builtins/ft_unset.c					\
				parsing/parse.c						\
				parsing/lists/ms_lstnew.c			\
				parsing/lists/ms_lstlast.c			\
				parsing/lists/ms_lstadd_back.c		\
				parsing/lists/ms_list_sort.c		\
				parsing/lists/ms_print_list.c		\
				parsing/split/ms_split_exp.c		\
				parsing/split/ms_split_var.c		

HFILES		=	minishell.h

LIB			=	libft.a

SOURCE		=	$(addprefix ./srcs/, $(FILES))
HEADERS		=	$(addprefix ./include/, $(HFILES))
INCLUDE		=	$(addprefix ./include/libft/, $(LIB))

OBJ			=	$(SOURCE:%.c=%.o)

CC			= 	clang

# ADD FLAGS

CFLAGS		= 	-I include/
FSANITIZE	= 	-g3 -O0 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@printf "[ $(NAME) ] Compiling...\r"
	@($(CC) -o $(NAME) $(SOURCE) $(INCLUDE) $(CFLAGS) $(FSANITIZE))
	@printf "[ $(NAME) ] Compiled \033[0;32mSuccessfully\n\033[0m"
	@./$(NAME)

lib:
	@make re bonus -C include/libft
	@make clean -C include/libft

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