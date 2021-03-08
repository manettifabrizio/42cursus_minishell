/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct1.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:28:28 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 17:40:40 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT1_H
# define STRUCT1_H

# include "libft/libft.h"

typedef enum e_token_type{
	PIPE,
	QUOTE,
	DQUOTE,
	SEMICOLON,  
	GREATER,
    DGREATER,
	LESSER,
    DLESSER,
    WORD,
} t_token_type;

typedef enum e_node_type {
    NODE_ARG,
    NODE_BUILTIN,
    NODE_REDIRECT_IN,
    NODE_REDIRECT_OUT,
    NODE_REDIRECT_OVER,
    NODE_PIPE,
    NODE_LINE
} t_node_type;

typedef struct s_token {
    char            *data;
    t_token_type    type;
} t_token;

typedef struct s_lexer {
    t_list  *tokens;
    int     nb_tokens;
} t_lexer;


typedef struct s_node {
    int             type;
    char            *data;
    struct s_node   *left;
    struct s_node   *right;
}   t_node;

#endif