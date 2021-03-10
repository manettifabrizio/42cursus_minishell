/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:15:30 by viroques          #+#    #+#             */
/*   Updated: 2021/03/09 18:56:07 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int         len_word(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_strchr("<>;|", str[i]))
            break;
        if (str[i] == '\\')
            i++;
        i++;
    }
    return (i);
}

static int      len_quote(char *str, char quote)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == quote && i > 0)
        {
            if (quote == '\'')
                return (i + 1);
            if (quote == '\"' && str[i - 1] != '\\')
                return (i + 1);
        }
        i++;
    }
    return (i);
}

char        *get_data_word(char *str)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!(new = malloc(sizeof(char) * ft_strlen(str) + 1)))
       return (NULL);
    while (str[i])
    {
        if (ft_strchr("<>;|", str[i]))
            break;
        if (str[i] == '\\')
            i++;
        new[j] = str[i];
        i++;
        j++;
    }
    new[j] = 0;
    return (new);
}

char        *get_data_quote(char *str, int len, char quote)
{
    char    *data;
    int     i;
    int     j;

    if (!(data = malloc(sizeof(char) * len + 1)))
        return (NULL);
    i = 1;
    j = 0;
    while (str[i])
    {
        if (str[i] == quote)
        {
            if (quote == '\'')
                break;
            if (quote == '\"' && str[i - 1] != '\\')
                break;
        }
        if (str[i] == '\\' && quote == '\"')
            if (str[i + 1] == '\\' || str[i + 1] == '\''
                || str[i + 1] == '\"')
                i++;
        data[j] = str[i];
        j++;
        i++;
    }
    data[j] = 0;
    return (data);
}

int         create_token(t_main *m, char *data, t_token_type type, t_lexer *lexer)
{
    t_list  *lst;
    t_token *token;
    int     len;

	lexer->nb_tokens = 0;
    if (!(token = malloc(sizeof(t_token))))
        malloc_error_1(m, lexer);
    token->type = type;
    if (type == WORD)
    {
        len = len_word(data);
        if (!(token->data = get_data_word(data)))
            malloc_error_1(m, lexer);
    }
    else if (type == D_QUOTE || type == S_QUOTE)
    {
        if (!(len = len_quote(data, data[0])))
            malloc_error_1(m, lexer);
        if (!(token->data = get_data_quote(data, len, data[0])))
            malloc_error_1(m, lexer);
        if (!ft_strchr(token->data, data[0]))
            token->type = WORD;
    }
    else
    {
        len = ft_strlen(data);
        if (!(token->data = ft_strdup(data)))
            malloc_error_1(m, lexer);
    }
    if (!(lst = ft_lstnew(token)))
        malloc_error_1(m, lexer);
	if (!(lexer->tokens))
		lexer->tokens = lst;
    else
		ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    return (len);
}