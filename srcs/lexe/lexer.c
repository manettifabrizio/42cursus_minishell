/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/10 14:24:55 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    is_an_operator(t_main *m, char c, char *next, t_lexer *lexer, int *i)
{
    if (c == '|')
        return (create_tok(m, "|", PIPE, lexer));
    if (c == ';')
        return (create_tok(m, ";", SEMICOLON, lexer));
    if (c == '>')
    {
        if (next && *next == '>')
        {
            *i += 1;
            return (create_tok(m, ">>", DGREATER, lexer));
        }
        return (create_tok(m, ">", GREATER, lexer));
    }
    if (c == '<')
    {
        if (next && *next == '<')
        {
            *i += 1;
            return (create_tok(m, "<<", DLESSER, lexer));
        }
        return (create_tok(m, "<", LESSER, lexer));
    }
    if (c == '\n')
        return (create_tok(m, "\n", NEWLINE, lexer));
    if (c == '\\')
    {
        if (next && (*next == D_QUOTE || *next == S_QUOTE))
        {
            *i += 1;
            return (create_tok(m, next, WORD, lexer));
        }
    }
    if (c == D_QUOTE)
        return (create_tok(m, "\"", DQUOTE, lexer));
    if (c == S_QUOTE)
        return (create_tok(m, "\'", SQUOTE, lexer));
    if (c == ' ')
        return (create_tok(m, " ", SPACE, lexer));
    return (0);
}
void        free_token(t_token *token)
{
    if (token->data)
        free(token->data);
    free(token);
}

int         check_closing_quote(t_list *tokens, t_token_type type)
{
    t_list *cur_tok;
    
    cur_tok = tokens->next;
    while (cur_tok)
    {
        if (t_access_tok(cur_tok)->type == type)
            return (1);
        cur_tok = cur_tok->next;
    }
    return (0);
}
int         handle_quote(t_list **prev, t_list **cur_tok, int type)
{
    if (!(check_closing_quote(*cur_tok, type)))
        return (type);
    del_cur_tok_and_link_next(prev, cur_tok);
    add_new_word(prev, cur_tok, type);
    return (0);
}

int         sorte_lexer(t_main *m, t_lexer *lexer)
{
    t_list *cur_tok;
    t_list *prev;
    int     type;
    (void)m;
    
    cur_tok = lexer->tokens;
    prev = cur_tok;
    while (cur_tok)
    {
        type = t_access_tok(cur_tok)->type;
        if (type == SPACE)
            del_cur_tok_and_link_next(&prev, &cur_tok);
        else if (type == DQUOTE || type == SQUOTE)
        {
            if (handle_quote(&prev, &cur_tok, type))
                return (type);
        }  
        else if (type == DLESSER)
        {
            prev = cur_tok;
            cur_tok = cur_tok->next;
            if (!cur_tok)
                return (0);
            while (t_access_tok(cur_tok)->type == SPACE)
                del_cur_tok_and_link_next(&prev, &cur_tok);
            
            type = t_access_tok(cur_tok)->type;
            if (type == DQUOTE || type == S_QUOTE)
            {
                if(handle_quote(&prev, &cur_tok, type))
                    return (type);
                heredoc(m, t_access_tok(prev)->data);
            }
            else if (type == WORD)
            {
                heredoc(m, t_access_tok(cur_tok)->data);
                prev = cur_tok;
                cur_tok = cur_tok->next;
            }
        }
        else if (type == PIPE)
        {
            if (!cur_tok->next)
                return (PIPE);
        }
        else
        {
            prev = cur_tok;
            cur_tok = cur_tok->next;
        }
    }
    return(0);
}

t_lexer     *build_lexer(t_main *m, char *s)
{
    int     i;
    t_lexer *lexer;
    
    i = 0;
    if (!(lexer = malloc(sizeof(t_lexer))))
        malloc_error(m, NULL, NO_READING);
    lexer->tokens = NULL;
    lexer->nb_tokens = 0;
    m->arr = ft_split_charset(s, " <>|;\'\"");
    while (m->arr[i])
    {
        if (is_an_operator(m, m->arr[i][0], m->arr[i + 1], lexer, &i));
        else
            create_tok(m, m->arr[i], WORD, lexer);
        i++;
    }
    sorte_lexer(m ,lexer);
    return (lexer);
}