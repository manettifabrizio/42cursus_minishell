# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/26 17:06:32 by fmanetti          #+#    #+#              #
#    Updated: 2021/03/04 12:10:42 by fmanetti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minish

FILES		=	minishell.c							\
				read/read.c							\
				read/check_keys.c					\
				read/str_print_and_handle.c			\
				read/ms_get_next_line.c				\
				keys/arrows.c						\
				keys/control.c						\
				keys/delete.c						\
				keys/home_end.c						\
				keys/word_move.c					\
				history/init_history.c				\
				history/history.c					\
				history/make_history.c				\
				execute/path.c						\
				execute/signals_term.c				\
				execute/heredoc.c					\
				builtins/builtins.c					\
				builtins/ft_echo.c					\
				builtins/ft_cd.c					\
				builtins/ft_pwd.c					\
				builtins/ft_export.c				\
				builtins/ft_unset.c					\
				builtins/ft_env.c					\
				builtins/ft_exit.c					\
				builtins/vars.c						\
				parse/env_path_parser.c				\
				parse/lists/ms_lstnew.c				\
				parse/lists/ms_lstlast.c			\
				parse/lists/ms_lstadd_back.c		\
				parse/lists/ms_list_sort.c			\
				parse/lists/ms_print_list.c			\
				parse/split/ms_split_exp.c			\
				parse/split/ms_split_var.c			\
				errors/error.c

HFILES		=	minishell.h

LIB			=	libft.a

SOURCE		=	$(addprefix ./srcs/, $(FILES))
HEADERS		=	$(addprefix ./include/, $(HFILES))
INCLUDE		=	$(addprefix ./include/libft/, $(LIB))

OBJ			=	$(SOURCE:%.c=%.o)

CC			= 	clang

CFLAGS		= 	-I include/ -Wall -Wextra -Werror
FSANITIZE	= 	-g3 -O0 -fsanitize=address

RED			=	\033[0;31m
GREEN		=	\033[0;32m
WHITE		=	\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@printf "[ $(NAME) ] Compiling...\r"
	@($(CC) -o $(NAME) $(SOURCE) $(INCLUDE) $(CFLAGS) $(FSANITIZE))
	@printf "${GREEN}"
	@printf "                          iiii                     iiii                  hhhhhhh                                lllllll lllllll  \n"
	@printf "                         i::::i                   i::::i                 h:::::h                                l:::::l l:::::l  \n"
	@printf "                          iiii                     iiii                  h:::::h                                l:::::l l:::::l  \n"
	@printf "                                                                         h:::::h                                l:::::l l:::::l  \n"
	@printf "   mmmmmmm    mmmmmmm   iiiiiiinnnn  nnnnnnnn    iiiiiii     ssssssssss   h::::h hhhhh           eeeeeeeeeeee    l::::l  l::::l  \n"
	@printf " mm:::::::m  m:::::::mm i:::::in:::nn::::::::nn  i:::::i   ss::::::::::s  h::::hh:::::hhh      ee::::::::::::ee  l::::l  l::::l  \n"
	@printf "m::::::::::mm::::::::::m i::::in::::::::::::::nn  i::::i ss:::::::::::::s h::::::::::::::hh   e::::::eeeee:::::eel::::l  l::::l  \n"
	@printf "m::::::::::::::::::::::m i::::inn:::::::::::::::n i::::i s::::::ssss:::::sh:::::::hhh::::::h e::::::e     e:::::el::::l  l::::l  \n"
	@printf "m:::::mmm::::::mmm:::::m i::::i  n:::::nnnn:::::n i::::i  s:::::s  ssssss h::::::h   h::::::he:::::::eeeee::::::el::::l  l::::l  \n"
	@printf "m::::m   m::::m   m::::m i::::i  n::::n    n::::n i::::i    s::::::s      h:::::h     h:::::he:::::::::::::::::e l::::l  l::::l  \n"
	@printf "m::::m   m::::m   m::::m i::::i  n::::n    n::::n i::::i       s::::::s   h:::::h     h:::::he::::::eeeeeeeeeee  l::::l  l::::l  \n"
	@printf "m::::m   m::::m   m::::m i::::i  n::::n    n::::n i::::i ssssss   s:::::s h:::::h     h:::::he:::::::e           l::::l  l::::l  \n"
	@printf "m::::m   m::::m   m::::mi::::::i n::::n    n::::ni::::::is:::::ssss::::::sh:::::h     h:::::he::::::::e         l::::::ll::::::l \n"
	@printf "m::::m   m::::m   m::::mi::::::i n::::n    n::::ni::::::is::::::::::::::s h:::::h     h:::::h e::::::::eeeeeeee l::::::ll::::::l \n"
	@printf "m::::m   m::::m   m::::mi::::::i n::::n    n::::ni::::::i s:::::::::::ss  h:::::h     h:::::h  ee:::::::::::::e l::::::ll::::::l \n"
	@printf "mmmmmm   mmmmmm   mmmmmmiiiiiiii nnnnnn    nnnnnniiiiiiii  sssssssssss    hhhhhhh     hhhhhhh    eeeeeeeeeeeeee llllllllllllllll \n"
	@printf "${WHITE}"
	@printf "┏┓ ╻ ╻   ┏━╸┏┳┓┏━┓┏┓╻┏━╸╺┳╸╺┳╸╻   ┏┓     ╻ ╻╻┏━┓┏━┓┏━┓╻ ╻┏━╸┏━┓     ┏━╸┏━┓┏┳┓┏━┓╻╻  ┏━╸╺┳┓  ${GREEN}┏━┓╻ ╻┏━╸┏━╸┏━╸┏━┓┏━┓┏━╸╻ ╻╻  ╻  ╻ ╻\n${WHITE}"
	@printf "┣┻┓┗┳┛   ┣╸ ┃┃┃┣━┫┃┗┫┣╸  ┃  ┃ ┃   ┃╺╋╸   ┃┏┛┃┣┳┛┃ ┃┃┓┃┃ ┃┣╸ ┗━┓     ┃  ┃ ┃┃┃┃┣━┛┃┃  ┣╸  ┃┃  ${GREEN}┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛\n${WHITE}"
	@printf "┗━┛ ╹    ╹  ╹ ╹╹ ╹╹ ╹┗━╸ ╹  ╹ ╹   ┗━┛    ┗┛ ╹╹┗╸┗━┛┗┻┛┗━┛┗━╸┗━┛     ┗━╸┗━┛╹ ╹╹  ╹┗━╸┗━╸╺┻┛  ${GREEN}┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹ \n${WHITE}"

lib:
	@make re bonus -C include/libft
	@make clean -C include/libft

key:
	@gcc -o key keycode.c $(CFLAGS)
	@./key
	@rm key

clean:
	@/bin/rm -f $(OBJ)
	@printf "Object files ${RED}removed\n${WHITE}"

fclean: clean
	@/bin/rm -rf $(NAME)*
	@/bin/rm -rf .vscode .minish_history
	@printf "[ $(NAME) ] ${RED}removed\n${WHITE}"

re: fclean all

.PHONY: all clean fclean re

.SILENT: