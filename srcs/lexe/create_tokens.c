/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:15:30 by viroques          #+#    #+#             */
/*   Updated: 2021/03/15 20:00:17 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int      create_tok(char *data, t_token_type type, t_lexer *lexer)
{
    t_list      *lst;
    t_token     *token;

    if (!(token = malloc(sizeof(t_token))))
        return (-1);
    token->type = type;
    if (!(token->data = ft_strdup(data)))
        return (-1);
    if(!(lst = ft_lstnew(token)))
        return (-1);
    if (!(lexer->tokens))
        lexer->tokens = lst;
    else
        ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    return (1);
}

static t_list        *generate_tok(char *data, t_token_type type, t_main *m)
{
    t_list      *lst;
    t_token     *token;

    if (!(token = malloc(sizeof(t_token))))
        malloc_error(m, NULL, NO_READING);
    token->type = type;
    if (!(token->data = ft_strdup(data)))
        malloc_error(m, NULL, NO_READING);
    if (!(lst = ft_lstnew(token)))
        malloc_error(m, NULL, NO_READING);
    return (lst);
}

void        del_cur_tok_and_link_next(t_list **prev, t_list **cur_tok)
{
    if ((*cur_tok)->next)
        (*prev)->next = (*cur_tok)->next;
    else
        (*prev)->next = NULL;
    free(t_access_tok(*cur_tok)->data);
    ft_lstdelone(*cur_tok, &free);
    (*cur_tok) = (*prev)->next;
}

char        *get_data_inside_quote(t_list **prev, t_list **cur_tok, t_token_type type, t_main *m)
{
    char *data;
    char *tmp;

    if (!(data = malloc(sizeof(char))))
        malloc_error(m, NULL, NO_READING);
    *data = '\0';
    tmp = data;
    while (*cur_tok && t_access_tok(*cur_tok)->type != type)
    {
        (*prev)->next = (*cur_tok)->next;
        tmp = data;
        if (!(data = ft_strjoin(tmp, t_access_tok(*cur_tok)->data)))
            malloc_error(m, NULL, NO_READING);
        free(tmp);
        free(t_access_tok(*cur_tok)->data);
        ft_lstdelone(*cur_tok, &free);
        *cur_tok = (*prev)->next;
    }
    if (type == SQUOTE)
        return (data);
    tmp = data;
    data = check_vars(m, data, m->ehead, m->exit_status);
    free(tmp);
    return (data);
}

void        add_new_word(t_list **prev, t_list **cur_tok, t_token_type type, t_main *m)
{
    char    *data;
    t_list  *new_word;
    
    data = get_data_inside_quote(prev, cur_tok, type, m);
    new_word = generate_tok(data, WORD, m);
    free(data);
    (*prev)->next = new_word;
    del_cur_tok_and_link_next(&new_word, cur_tok);
    *prev = new_word;
}
