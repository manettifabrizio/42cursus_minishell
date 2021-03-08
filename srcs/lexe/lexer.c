/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/08 21:36:31 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int     is_an_operator(t_main *m, char c, char *next, t_lexer *lexer)
{
    if (c == '|')
        return (create_token(m, "|", PIPE, lexer));
    if (c == ';')
        return (create_token(m, ";", SEMICOLON, lexer));
    if (c == '>')
    {
        if (next && *next == '>')
            return (create_token(m, ">>", DGREATER, lexer));
        return (create_token(m, ">", GREATER, lexer));
    }
    if (c == '<')
    {
        if (next && *next == '<')
        {
            //heredoc
            return (-2);
        }
        return (create_token(m, "<", LESSER, lexer));
    }
    return (0);
}

int     build_lexer(t_main *m, char *s, t_lexer *lexer)
{
    int i;
    int j;
    int ret;

    i = 0;
    j = 0;
    m->arr = ft_split(s, ' ');
    while (m->arr[i])
    {
        j = 0;
        while (m->arr[i][j])
        {
            if ((ret = is_an_operator(m, m->arr[i][j], m->arr[i] + j + 1, lexer)));
            else if (m->arr[i][j] == '\"')
                ret = create_token(m, m->arr[i] + j, DQUOTE, lexer);
            else if (m->arr[i][j] == '\'')
                ret = create_token(m, m->arr[i] + j, QUOTE, lexer);
            else
                ret = create_token(m, m->arr[i] + j, WORD, lexer);
            if (ret < 0)
                return (ret);
            j += ret;
        }
        i++;
    }
    return (0);
}