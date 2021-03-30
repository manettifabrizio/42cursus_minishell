/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:26:57 by viroques          #+#    #+#             */
/*   Updated: 2021/03/18 13:48:34 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node		*build_command_heredoc(t_list **token)
{
	t_node	*result;
	t_node	*builtin;
	char	*filename;

	if ((builtin = build_builtin(token)) == NULL)
		return (NULL);
	if (!check(DLESSER, NULL, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!check(WORD, &filename, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!(result = create_node(NODE_REDIRECT_HEREDOC, filename)))
		return (NULL);
	ast_attach_branch(result, builtin, build_filename(token));
	return (result);
}

static t_node		*build_command_over(t_list **token)
{
	t_node	*result;
	t_node	*builtin;
	char	*filename;

	if ((builtin = build_builtin(token)) == NULL)
		return (NULL);
	if (!check(DGREATER, NULL, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!check(WORD, &filename, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!(result = create_node(NODE_REDIRECT_OVER, filename)))
		return (NULL);
	ast_attach_branch(result, builtin, build_filename(token));
	return (result);
}

static t_node		*build_command_out(t_list **token)
{
	t_node	*result;
	t_node	*builtin;
	char	*filename;

	if ((builtin = build_builtin(token)) == NULL)
		return (NULL);
	if (!check(LESSER, NULL, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!check(WORD, &filename, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!(result = create_node(NODE_REDIRECT_OUT, filename)))
		return (NULL);
	ast_attach_branch(result, builtin, build_filename(token));
	return (result);
}

static t_node		*build_command_in(t_list **token)
{
	t_node	*result;
	t_node	*builtin;
	char	*pathname;

	if ((builtin = build_builtin(token)) == NULL)
		return (NULL);
	if (!check(GREATER, NULL, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!check(WORD, &pathname, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!(result = create_node(NODE_REDIRECT_IN, pathname)))
		return (NULL);
	ast_attach_branch(result, builtin, build_filename(token));
	return (result);
}

t_node				*build_command(t_list **token)
{
	t_node *node;
	t_list *save;

	save = *token;
	if ((*token = save)
		&& (node = build_command_in(token)))
		return (node);
	if ((*token = save)
		&& (node = build_command_out(token)))
		return (node);
	if ((*token = save)
		&& (node = build_command_over(token)))
		return (node);
	if ((*token = save)
		&& (node = build_command_heredoc(token)))
		return (node);
	if ((*token = save)
		&& (node = build_command_builtin(token)))
		return (node);
	return (NULL);
}
