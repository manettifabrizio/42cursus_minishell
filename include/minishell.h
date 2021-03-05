/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:37:24 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/05 11:25:40 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <math.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>

# include "struct.h"
# include "keys.h"
# include "libft/libft.h"

int signaln;

typedef struct dirent	t_dir;

// READ
char				*line_read(t_main *m);
int					check_key(t_main *m, char **s, char *buf);
char 				*str_print_and_handle(t_main *m, char *s, char *buf, t_cursor pos);
char				*inword_erase(char *s, t_uint len);
int					ms_get_next_line(int fd, char **line);

// HISTORY
char				**init_history();
char				**history(char *s, char **a, t_uint i, t_uint posy);
void				make_history(char *hist_path, char **h);

// PARSE
t_env				*env_parser(t_env *head, char **env);
char				**path_parser(t_env *head);
char				*get_env(t_env *head, char *name);
void				set_env(t_env *head, char *name, char *value);

//EXECUTE
void				line_execute(t_main *m, char **env);
int					search_path(t_main *m, char **env);
void				ft_signal(int num);
void				config_term(int n, struct termios *base_term);
int					heredoc(t_main *m, char *keywrd);

// BUILTINS
int					builtins(t_main *m);
int					ft_echo(t_main *m, char **a, t_env *head);
int					ft_cd(t_main *m, char *s);
int					ft_pwd(t_main *m, t_env *head);
int					ft_export(t_main *m, char **a, t_env *head);
int					ft_unset(t_main *m, char **a, t_env *head);
int					ft_env(t_main *m, t_env *head);
int					ft_exit(t_main *m, char **a);
char				*check_vars(char *s, t_env *head, int exit_status);

// LISTS
t_env				*ft_lstnew_e();
t_env				*ft_lstlast_e(t_env *lst);
void				ft_lstadd_back_e(t_env **alst, t_env *new);
void				ms_print_list(t_env *head);
t_env				*ms_list_sort(t_env *head);

// SPLIT
char				**ms_split_exp(char const *s, char c);
char				**ms_split_var(char *s);

// ERRORS
int					error(int errtype, char *message);
int					status_error(t_main *m, int errtype, int status, char *message);

#endif