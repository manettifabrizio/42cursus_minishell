/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/10 12:50:21 by fmanetti         ###   ########.fr       */
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
            || t_access_tok(lst->next)->type == S_QUOTE
            || t_access_tok(lst->next)->type == D_QUOTE)
                return (lst);
        }
        if (t_access_tok(lst)->type == PIPE)
            if (!lst->next)
                return (lst);
        lst = lst->next;
    }
    return (lst);
}

static int		here_or_multi(t_main *m, t_lexer *lexer, char *s)
{
	t_list	*l;
	t_token	*tmp;

	if ((l = check_lexer(lexer)))
	{
		tmp = t_access_tok(l);
		if (tmp->type == DLESSER)
		{
			if (!(heredoc(m, t_access_tok(l->next)->data)))
				return (0);
		}
		else if (tmp->type == PIPE || tmp->type == D_QUOTE || 
			tmp->type == S_QUOTE)
		{
			// printf("data=%s type= %i\n", tmp->data, tmp->type);
			ft_free_array(m->arr);
			s = multilines(m, s, tmp->type);
			free_lexer(lexer);
			lexer = NULL;
			build_lexer(m, s);
		}
	}
	return (1);
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
	if (!(ft_strchr(s, '\"')) && !(ft_strchr(s, '\'')))
    	m->arr = ft_split(s, ' ');
	else
		return (NULL);
	// 	lexe_multi();
	// printf("**************************\n");
    while (m->arr[i])
    {
        j = 0;
        while (m->arr[i][j])
        {
            if ((ret = is_an_operator(m, m->arr[i][j], m->arr[i] + j + 1, lexer)));
            else if (m->arr[i][j] == '\"')
                ret = create_token(m, m->arr[i] + j, D_QUOTE, lexer);
            else if (m->arr[i][j] == '\'')
                ret = create_token(m, m->arr[i] + j, S_QUOTE, lexer);
            else
                ret = create_token(m, m->arr[i] + j, WORD, lexer);
            if (ret < 0)
                return (NULL);
            j += ret;
        }
        i++;
    }
	if (!(here_or_multi(m, lexer, s)))
		return (NULL);
    return (lexer);
}