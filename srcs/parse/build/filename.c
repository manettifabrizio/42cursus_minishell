/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:29:11 by viroques          #+#    #+#             */
/*   Updated: 2021/03/08 17:37:23 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node      *build_filename_1(t_list **token)
{
    t_node  *result;
    char    *pathname;

    if (!check(GREATER, NULL, token))
        return (NULL);
    if (!check(WORD, &pathname, token))
        return (NULL);
    if (!(result = malloc(sizeof(t_node))))
        return (NULL);
    ast_set_data(result, pathname);
    ast_set_type(result, NODE_REDIRECT_IN);
    ast_attach_branch(result, NULL, build_filename(token));
    return (result);
}

static t_node      *build_filename_2(t_list **token)
{
    t_node  *result;
    char    *pathname;

    if (!check(DGREATER, NULL, token))
        return (NULL);
    if (!check(WORD,&pathname, token))
        return (NULL);
    if (!(result = malloc(sizeof(t_node))))
        return (NULL);
    ast_set_data(result, pathname);
    ast_set_type(result, NODE_REDIRECT_OVER);
    ast_attach_branch(result, NULL, build_filename(token));
    return (result);
}

static t_node          *build_filename_3(t_list **token)
{
    (void)token;
    return (NULL);
}

t_node      *build_filename(t_list **token)
{
    t_list *save;
    t_node *node;

    save = *token;
    if ((*token = save) && (node = build_filename_1(token)))
        return (node);
    if ((*token = save) && (node = build_filename_2(token)))
        return (node);
    if ((*token = save) && (node = build_filename_3(token)))
        return (node);
    return NULL;
}