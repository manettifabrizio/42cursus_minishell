/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:29:11 by viroques          #+#    #+#             */
/*   Updated: 2021/03/29 15:08:01 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*build_filename_in(t_list **token)
{
	t_node	*result;
	char	*pathname;

	if (!check(GREATER, NULL, token))
		return (NULL);
	if (!check(WORD, &pathname, token))
		return (NULL);
	if (!(result = create_node(NODE_REDIRECT_IN, pathname)))
		return (NULL);
	ast_attach_branch(result, NULL, build_filename(token));
	return (result);
}

static t_node	*build_filename_over(t_list **token)
{
	t_node	*result;
	char	*pathname;

	if (!check(DGREATER, NULL, token))
		return (NULL);
	if (!check(WORD, &pathname, token))
		return (NULL);
	if (!(result = create_node(NODE_REDIRECT_OVER, pathname)))
		return (NULL);
	ast_attach_branch(result, NULL, build_filename(token));
	return (result);
}

static t_node	*build_filename_out(t_list **token)
{
	t_node	*result;
	char	*pathname;

	if (!check(LESSER, NULL, token))
		return (NULL);
	if (!check(WORD, &pathname, token))
		return (NULL);
	if (!(result = create_node(NODE_REDIRECT_OUT, pathname)))
		return (NULL);
	ast_attach_branch(result, NULL, build_filename(token));
	return (result);
}

static t_node	*build_filename_empty(t_list **token)
{
	(void)token;
	return (NULL);
}

t_node			*build_filename(t_list **token)
{
	t_list *save;
	t_node *node;

	save = *token;
	if ((*token = save)
		&& (node = build_filename_in(token)))
		return (node);
	if ((*token = save)
		&& (node = build_filename_over(token)))
		return (node);
	if ((*token = save)
		&& (node = build_filename_out(token)))
		return (node);
	if ((*token = save)
		&& (node = build_filename_empty(token)))
		return (node);
	return (NULL);
}
