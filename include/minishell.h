/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:37:24 by fmanetti          #+#    #+#             */
/*   Updated: 2021/01/29 14:40:53 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include "libft/libft.h"

typedef struct dirent t_dir;

typedef	struct		s_tree
{
	char			*word1;
	char			*word2;
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
	char			**path;
	char			*str;
}					t_main;

void				line_parse(t_main *m, char **env);
void				line_execute(t_main m, char **env);
int					search_path(t_main m, char **env);

// LISTS
t_env				*ft_lstnew_e();
t_env				*ft_lstlast_e(t_env *lst);
void				ft_lstadd_back_e(t_env **alst, t_env *new);
void				ft_print_list(t_env *head);
