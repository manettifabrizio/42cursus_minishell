/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:26:01 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/09 14:33:23 by viroques         ###   ########.fr       */
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
	t_uint			x;
	t_uint			y;
}					t_cursor;

typedef enum		e_token_type{
	PIPE,
	QUOTE,
	DQUOTE,
	SEMICOLON,
	GREATER,
	DGREATER,
	LESSER,
	DLESSER,
	WORD,
}					t_token_type;

typedef enum		e_node_type {
	NODE_ARG,
	NODE_BUILTIN,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_OVER,
	NODE_REDIRECT_HEREDOC,
	NODE_PIPE,
	NODE_LINE
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


typedef	struct		s_main
{
	char			**env;
	char			*home;
	t_list			**ehead;
	t_cursor		*pos;
	char			**hist;
	char			*hist_path;
	int				exit_status;
	// commands
	char			**arr;
	// path variable
	char			**pathdirs;
	//multilines
	t_uint			multilns;
	struct termios	*base_term;
}					t_main;

#endif
