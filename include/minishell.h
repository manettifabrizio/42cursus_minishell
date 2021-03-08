/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:37:24 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 21:32:41 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <math.h>
// # include <curses.h>
// # include <term.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/types.h>
# include "struct.h"
# include "keys_and_errors.h"


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

// LEXER
int         		build_lexer(t_main *m, char *s, t_lexer *lexer);
int         		create_token(t_main *m, char *data, t_token_type type, t_lexer *lexer);

// PARSE
t_list				**env_parser(t_list **head, char **env);
char				**path_parser(t_list **head);
char				*get_env(t_list **head, char *name);
void				set_env(t_list **head, char *name, char *value);

int         		parse(t_lexer *lexer, t_node **exec_tree);
t_node      		*build_line(t_list **token);
t_node      		*build_job(t_list **token);
t_node      		*build_command(t_list **token);
t_node      		*build_filename(t_list **token);
t_node      		*build_builtin(t_list **token);
t_node      		*build_args(t_list **token);
int         		check(t_token_type tok_type, char** bufferptr, t_list **token);

//EXECUTE
void				ft_signal(int num);
void				config_term(int n, struct termios *base_term);
int					heredoc(t_main *m, char *keywrd);
void                execute_simple_pipe(t_main *m, t_node *node_pipe);
int					execute_bin(t_main *m, t_node *cmd);
void        		handle_redirection(t_node *node_redirect);
char        		*search_path(char *cmd_name, char **directories);
char        		**get_directories_path(char **env);
void     			execute_ast_tree(t_main *m, t_node *exec_tree);
char                **create_cmd_table(t_node *root);

// BUILTINS
int					builtins(t_main *m, char *cmd_name);
int					ft_echo(t_main *m, char **a, t_list **head);
int					ft_cd(t_main *m, char *s);
int					ft_pwd(t_main *m, t_list **head);
int					ft_export(t_main *m, char **a, t_list **head);
int					ft_unset(t_main *m, char **a, t_list **head);
int					ft_env(t_main *m, t_list **head);
int					ft_exit(t_main *m, char **a);
char				*check_vars(t_main *m, char *s, t_list **head, int exit_status);

// LISTS
t_token     		*t_access_tok(t_list *lst);
t_env	     		*t_access_env(t_list *lst);
t_list				*list_sort(t_list **head);
void				print_list(t_list **head);

// AST TREE
void        		ast_delete_node(t_node *node);
void        		ast_set_data(t_node *node, char *data);
void        		ast_set_type(t_node *node, int type);
void        		ast_attach_branch(t_node *root, t_node *left, t_node *right);

// SPLIT
char				**ms_split_exp(char const *s, char c);
char				**ms_split_var(char *s);

// KEYS
int					arrow_up(char **s, char **h, t_cursor *pos);
int					arrow_down(char **s, char **h, t_cursor *pos);
int					arrow_right(t_cursor *pos);
int					arrow_left(char *s, t_cursor *pos);
int					control_c(t_main *m, char *s);
int					control_d(t_main *m);
int					backspace(char *s, t_cursor pos);
int					delete(char *s, char *buf, t_cursor *pos);
int					home(char *s, t_cursor *pos);
int					end(t_cursor *pos);
int					word_right(char *s, t_cursor *pos);
int					word_left(char *s, t_cursor *pos);

// ERRORS and FREE
int					error(int errtype, char *message);
int					status_error(t_main *m, int errtype, int status, char *message);
void				malloc_error(t_main *m, char *s, int errtype);
int         		error_parsing(char *data);
void				free_all(t_main *m);
void				free_lexer(t_list *lst_tokens);
int		            malloc_error_1(t_main *m);
char		        *malloc_error_2(t_main *m);

// UTILS
t_list				*create_env_elem(char **a);

#endif