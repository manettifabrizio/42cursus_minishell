/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:37:24 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/22 16:56:00 by fmanetti         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/types.h>
# include "struct.h"
# include "macros.h"

typedef struct dirent	t_dir;

// INIT
void				set_term_noncano();
void				set_term_cano(struct termios *base_term);

// READ
char				*line_read(t_main *m);
int					reading(t_main *m, char **s, char *buf);
int					check_key(t_main *m, char **s, char *buf);
int					arrows(t_main *m, char **s, char c);
int					home_end(char *s, char c, t_cursor *p);
int					word_move(char *s, t_cursor *p);
char 				*str_print_and_handle(t_main *m, char *s, char *buf, t_cursor *p);
int					heredoc(t_main *m, char *keywrd);
int					check_key_heredoc(t_main *m, char **s, char *buf);
char				*multilines(t_main *m, char *s, t_token_type type);
int					check_multi(char *s, t_token_type type, int x);

// WILDCARD
char				*star_to_str(char *s, char *path, t_list **head);
t_list				*star(char *s, int *i, t_list **head);
int					starcmp(char *s, char *s1);

// HISTORY
char				**init_history();
char				**history(char *s, char **a, t_uint hnum);
char				**add_history(char *s, char **a);
void				make_history(char *hist_path, char **h);
int					get_next_separator(int fd, char **line);

// LEXER
t_lexer         	*build_lexer(t_main *m, char *s);
int                 create_tok(char *data, t_token_type type, t_lexer *lexer);
char	            **ft_split_charset(const char *s, char *charset);
void                del_cur_tok_and_link_next(t_list **prev, t_list **cur_tok);
char                *get_data_inside_quote(t_list **prev, t_list **cur_tok, t_token_type type, t_main *m);
void                 add_new_word(t_list **prev, t_list **cur_tok, t_token_type type, t_main *m);
void                print_lst_tokens(t_lexer *lexer);
int                 sort_lexer(t_main *m, t_lexer *lexer);
int                 check_closing_quote(t_list *tokens, t_token_type type);
int                 check_pre_space(t_lexer *lexer);
void                word_interpolation(t_main *m, t_list **cur_tok, t_list **prev);

// PARSE
t_list				**env_parser(t_list **head, char **env);
char				**path_parser(t_list **head);
char				*get_env(t_list **head, char *name);
void				set_env(t_list **head, char *name, char *value);
t_list				*create_env_elem(char **a);
int         		parse(t_lexer *lexer, t_node **exec_tree);
t_node      		*build_line(t_list **token, int par);
t_node				*build_line_job(t_list **token);
t_node      		*build_job(t_list **token);
t_node      		*build_command(t_list **token);
t_node				*build_command_builtin(t_list **token);
t_node      		*build_filename(t_list **token);
t_node      		*build_builtin(t_list **token);
t_node      		*build_args(t_list **token);
int         		check(t_token_type tok_type, char** bufferptr, t_list **token);
int                 check_par(t_token_type tok_type, char** bufferptr, t_list **token);
t_node              *check_closing_par(int par, t_list **token, t_node *node);
t_node              *create_node(int type, char *data);

//EXECUTE
void				ft_signal(int num);
void				execute_simple_pipe(t_main *m, t_node *node_pipe);
int					execute_bin(t_main *m, t_node *cmd);
void        		handle_redirection(t_node *node_redirect);
char        		*search_path(char *cmd_name, char **directories);
char        		**get_directories_path(char **env);
void     			execute_ast_tree(t_main *m, t_node *exec_tree);
char                **create_cmd_table(t_node *root);

// BUILTINS
int					builtins(t_main *m, char *cmd_name);
int					ft_echo(t_main *m, char **a);
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
t_files				*t_access_files(t_list *lst);
t_list				*list_sort(t_list **head);
void				print_list(t_list **head);

// AST TREE
void        		ast_delete_node(t_node *node);
void        		ast_set_data(t_node *node, char *data);
void        		ast_set_type(t_node *node, int type);
void        		ast_attach_branch(t_node *root, t_node *left, t_node *right);
void                ast_attach_right(t_node *root, t_node *right);

// SPLIT
char				**split_exp(char const *s, char c);
char				**split_var(char *s);
char				**split_keep(char *s, char c);

// KEYS
int					arrow_up(char **s, char **h, t_cursor *p);
int					arrow_down(char **s, char **h, t_cursor *p);
int					arrow_right(char *s, t_cursor *p);
int					arrow_left(char *s, t_cursor *p);
int					control_c(t_main *m, char *s);
void				control_d(t_main *m);
int					backspace(char *s, t_cursor *p);
int					delete(char *s, char *buf, t_cursor *p);
int					home(char *s, t_cursor *p);
int					end(char *s, t_cursor *p);
int					word_right(char *s, t_cursor *p);
int					word_left(char *s, t_cursor *p);
int					column_up(char *s, t_cursor *p);
int					column_down(char *s, t_cursor *p);

// ERRORS and FREE
int					error(int errtype, char *message);
int					status_error(t_main *m, int errtype, int status, char *message);
void				malloc_error(t_main *m, char *s, int errtype);
void                malloc_error_lexer(t_main *m, t_lexer *lexer);
int         		error_parsing(char *data);
void				free_all(t_main *m);
void				free_lexer(t_lexer *lexer);

// UTILS
t_uint				count_lines(char *s);
void				changing_line(t_cursor *p);

#endif