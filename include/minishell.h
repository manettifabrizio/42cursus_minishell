/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:37:24 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/27 21:07:58 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <math.h>
// # include <curses.h>
// # include <term.h>
# include "libft/libft.h"

int signaln;

#define		CURSOR_LEFT		"\033[D"
#define		CURSOR_RIGHT	"\033[C"
#define		CLEAR_LINE		"\033[0K"

#define		SEPARATOR		31

#define		CTRL_C			3
#define		CTRL_D			4
#define		ESCAPE			27
#define		CTRL_BSLASH		28
#define		DELETE			51
#define		ARR_UP			65
#define		ARR_DOWN		66
#define		ARR_RIGHT		67
#define		ARR_LEFT		68
#define		END				70
#define		HOME			72
#define		BACKSPACE		127

typedef struct dirent	t_dir;
typedef unsigned int	t_uint;

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

typedef struct		s_cursor
{
	t_uint	x;
	t_uint	y;
}					t_cursor;

typedef	struct		s_main
{
	t_tree			*thead;
	t_env			*ehead;
	t_cursor		*pos;
	char			**hist;
	// commands
	char			**arr;
	// path variable
	char			**path;
	struct termios	*base_term;
}					t_main;

// READ
char				*line_read(t_main *m);
int					check_key(char **s, char *buf, t_main *m);
char 				*str_print_and_handle(char *s, char *buf, t_cursor pos);
char				*inword_erase(char *s, t_uint len);
int					ms_get_next_line(int fd, char **line);

// HISTORY
char				**init_history();
char				**history(char *s, char **a, t_uint i, t_uint posy);
void				make_history(char **h);

// PARSE
void				shell_parse(t_main *m, char **env);

//EXECUTE
void				line_execute(t_main *m, char **env);
int					search_path(t_main m, char **env);
void				ft_signal(int num);
void				set_term(int n, struct termios *base_term);
int					heredoc(t_main *m, char *keywrd);

// BUILTINS
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

// KEYS
int					arrow_up(char **s, char **h, t_cursor *pos);
int					arrow_down(char **s, char **h, t_cursor *pos);
int					arrow_right(t_cursor *pos);
int					arrow_left(char *s, t_cursor *pos);
int					control_c(char *s);
int					control_d(struct termios *base_term, char **h);
int					backspace(char *s, t_cursor pos);
int					delete(char *s, char *buf, t_cursor *pos);
int					home(char *s, t_cursor *pos);
int					end(t_cursor *pos);