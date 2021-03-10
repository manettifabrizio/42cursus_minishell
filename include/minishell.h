/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:37:24 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 14:30:55 by viroques         ###   ########.fr       */
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
# include "macros.h"

typedef struct dirent	t_dir;

// INIT
void				set_term_noncano();
void				set_term_cano(struct termios *base_term);

// READ
char				*line_read(t_main *m);
int					check_key(t_main *m, char **s, char *buf);
int					arrows(t_main *m, char **s, char c);
int					home_end(char *s, char c, t_cursor *pos);
int					word_move(char *s, t_cursor *pos);
char 				*str_print_and_handle(t_main *m, char *s, char *buf, t_cursor pos);
char				*inword_erase(char *s, t_uint len);
int					heredoc(t_main *m, char *keywrd);
int					check_key_heredoc(t_main *m, char **s, char *buf);
char				*multilines(t_main *m, char *s, t_token_type type);


// HISTORY
char				**init_history();
char				**history(char *s, char **a, t_uint i, t_uint posy);
void				make_history(char *hist_path, char **h);
int					get_next_separator(int fd, char **line);

// LEXER
t_lexer         	*build_lexer(t_main *m, char *s);
int                 create_tok(t_main *m, char *data, t_token_type type, t_lexer *lexer);
char	            **ft_split_charset(const char *s, char *charset);
t_list              *generate_tok(char *data, t_token_type type);
void                del_cur_tok_and_link_next(t_list **prev, t_list **cur_tok);
char                *get_data_inside_quote(t_list **prev, t_list **cur_tok, t_token_type type);
void                add_new_word(t_list **prev, t_list **cur_tok, t_token_type type);
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
void				execute_simple_pipe(t_main *m, t_node *node_pipe);
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
char				**split_exp(char const *s, char c);
char				**split_var(char *s);

// KEYS
int					arrow_up(char **s, char **h, t_cursor *pos);
int					arrow_down(char **s, char **h, t_cursor *pos);
int					arrow_right(t_cursor *pos);
int					arrow_left(char *s, t_cursor *pos);
int					control_c(t_main *m, char *s);
void				control_d(t_main *m);
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
void                malloc_error_1(t_main *m, t_lexer *lexer);
int         		error_parsing(char *data);
void				free_all(t_main *m);
void				free_lexer(t_lexer *lexer);

// UTILS
t_list				*create_env_elem(char **a);

#endif