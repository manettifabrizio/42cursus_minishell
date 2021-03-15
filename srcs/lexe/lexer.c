/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/15 19:37:45 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int         is_quote_or_space(char c, char *next, t_lexer *lexer, int *i)
{
    if (c == '\n')
        return (create_tok("\n", NEWLINE, lexer));
    if (c == '\\')
    {
        if (next && (*next == '\"' || *next == '\''))
        {
            *i += 1;
            return (create_tok(next, WORD, lexer));
        }
    }
    if (c == '\"')
        return (create_tok("\"", DQUOTE, lexer));
    if (c == '\'')
        return (create_tok("\'", SQUOTE, lexer));
    if (c == ' ')
        return (create_tok(" ", SPACE, lexer));
    return (0);
}

static int         is_an_operator(char c, char *next, t_lexer *lexer, int *i)
{
    if (c == '|')
        return (create_tok("|", PIPE, lexer));
    if (c == ';')
        return (create_tok(";", SEMICOLON, lexer));
    if (c == '>')
    {
        if (next && *next == '>')
        {
            *i += 1;
            return (create_tok(">>", DGREATER, lexer));
        }
        return (create_tok(">", GREATER, lexer));
    }
    if (c == '<')
    {
        if (next && *next == '<')
        {
            *i += 1;
            return (create_tok("<<", DLESSER, lexer));
        }
        return (create_tok("<", LESSER, lexer));
    }
    return (is_quote_or_space(c, next, lexer, i));
}

static t_lexer     *init_lexer(t_main *m, char *s)
{
    t_lexer *lexer;

     if (!(lexer = malloc(sizeof(t_lexer))))
        malloc_error(m, NULL, NO_READING);
    lexer->tokens = NULL;
    lexer->nb_tokens = 0;
    if (!(m->arr = ft_split_charset(s, " <>|;\'\"\n")))
        malloc_error_lexer(m, lexer);
    return (lexer);
}

t_lexer     *build_lexer(t_main *m, char *s)
{
    int     i;
    t_lexer *lexer;
    int     type;
    int     ret;

    lexer = init_lexer(m, s);
    i = 0;
    while (m->arr[i])
    {
        if ((ret = is_an_operator(m->arr[i][0], m->arr[i + 1], lexer, &i)));
        else
            ret = create_tok(m->arr[i], WORD, lexer);
        if (ret == -1)
            malloc_error_lexer(m, lexer);
        i++;
    }
    if ((type = sort_lexer(m ,lexer)) > 0)
    {
        ft_free_array(m->arr);
		s = multilines(m, s, type);
		free_lexer(lexer);
		lexer = NULL;
		// printf("hists = |%s|\n", s);
		return (build_lexer(m, s));
    }
    if (type == -1)
        return (NULL);
    return (lexer);
}