/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/09 15:06:01 by viroques         ###   ########.fr       */
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
            return (create_token(m, "<<", DLESSER, lexer));
        return (create_token(m, "<", LESSER, lexer));
    }
    return (0);
}

t_list      *check_lexer(t_lexer *lexer)
{
    t_list *lst;

    if (lexer->nb_tokens == 0)
        return (0);
    lst = lexer->tokens;
    while (lst)
    {
        if (t_access_tok(lst)->type == DLESSER)
        {
            if (!lst->next)
            {
                // parser will throw a syntax error so continue
                return (NULL);
            }
            if (t_access_tok(lst->next)->type == WORD
            || t_access_tok(lst->next)->type == QUOTE
            || t_access_tok(lst->next)->type == DQUOTE)
                return (lst);
        }
        if (t_access_tok(lst)->type == PIPE)
            if (!lst->next)
                return (lst);
        lst = lst->next;
    }
    return (lst);
}

t_lexer     *build_lexer(t_main *m, char *s)
{
    int i;
    int j;
    int ret;
    t_lexer *lexer;

    i = 0;
    j = 0;
    if (!(lexer = malloc(sizeof(t_lexer))))
        malloc_error(m, NULL, NO_READING);
    lexer->tokens = NULL;
    lexer->nb_tokens = 0;
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
                return (NULL);
            j += ret;
        }
        i++;
    }
    t_list *toto;
    if ((toto = check_lexer(lexer)) != NULL)
    {
        if (t_access_tok(toto)->type == DLESSER)
            heredoc(m, t_access_tok(toto->next)->data);
        else if (t_access_tok(toto)->type == PIPE)
        {
            printf("data=%s type= %i\n", t_access_tok(toto)->data, t_access_tok(toto)->type);
            // ft_free_array(m->arr);
            // free_lexer(lexer);
            // lexer = NULL;
            // call multiligne
            // call build lexer again with new line from multiligne
        }
        else if (t_access_tok(toto)->type == DQUOTE || t_access_tok(toto)->type == S_QUOTE)
        {
            printf("data=%s type= %i\n", t_access_tok(toto)->data, t_access_tok(toto)->type);
            // ft_free_array(m->arr);
            // free_lexer(lexer);
            // lexer = NULL;
            // call multiligne , dont stop until found a closing quote
            // call build lexer again with new line from multiligne
        }
    }
    return (lexer);
}