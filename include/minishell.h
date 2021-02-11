/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:37:24 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/11 13:43:40 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>
#include <string.h>
#include "libft/libft.h"

typedef struct dirent t_dir;

typedef	struct		s_tree
{
	char			*w1;
	char			*w2;
}					t_tree;

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef	struct		s_main
{
	t_tree			*thead;
	t_env			*ehead;
	// commands
	char			**arr;
	// path variable
	char			**path;
}					t_main;

char				**line_read();
void				line_parse(t_main *m, char **env);
void				line_execute(t_main *m, char **env);
int					search_path(t_main m, char **env);

int					builtins(t_main *m);
int					ft_echo(char **a, t_env *head);
int					ft_export(char **a, t_env *head);
int					ft_unset(char **a, t_env *head);

// LISTS
t_env				*ft_lstnew_e();
t_env				*ft_lstlast_e(t_env *lst);
void				ft_lstadd_back_e(t_env **alst, t_env *new);
void				ms_print_list(t_env *head);
t_env				*ms_list_sort(t_env *head);

// SPLIT
char				**ms_split_exp(char const *s, char c);
char				**ms_split_var(char *s);
