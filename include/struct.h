/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:26:01 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/02 11:49:55 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft/libft.h"

typedef unsigned int	t_uint;

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_cursor
{
	t_uint			multi;	// Value that indicates if we are in multilines mode
	t_uint			lpos;	// Cursor position in line
	t_uint			spos;	// Cursor position in whole string
	t_uint			hnum;	// Line position in history array 
	t_uint			lnum;	// Line position in multilines
	char			**arr;	// Array used in multilines
}					t_cursor;

typedef struct		s_files
{
	char			*name;
}					t_files;


typedef enum		e_token_type{
	SEMICOLON,
	NEWLINE,
	PIPE,
	SQUOTE,
	DQUOTE,
	GREATER,
	DGREATER,
	LESSER,
	DLESSER,
	WORD,
	SPACE,
	DAMPERSTAND,
	DPIPE,
	OPEN_PAR,
	CLOSE_PAR,
	CHAR_NULL,
	WILDCARD,
	BACKSLASH
}					t_token_type;

typedef enum		e_node_type {
	NODE_ARG,
	NODE_BUILTIN,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_OVER,
	NODE_REDIRECT_HEREDOC,
	NODE_PIPE,
	NODE_LINE,
	NODE_LOGIC_PIPE,
	NODE_LOGIC_AMPERSTAND,
}					t_node_type;

typedef struct		s_token {
	char			*data;
	t_token_type	type;
}					t_token;

typedef struct		s_lexer {
	t_list			*tokens;
	int				nb_tokens;
}					t_lexer;

typedef struct		s_node {
	int				type;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct		s_std{
	int fd_in;
	int	fd_out;
	int fd[2];
	int	tmp_in;
	int	tmp_out;
}				t_std;

typedef	struct		s_main
{
	char			**env;
	char			*home;
	t_list			**ehead;
	t_cursor		*p;
	char			**hist;
	char			*hist_path;
	int				exit_status;
	char			**arr;
	char			**pathdirs;
	t_uint			multilns;
	struct termios	*base_term;
}					t_main;

#endif