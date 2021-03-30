/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:21:26 by viroques          #+#    #+#             */
/*   Updated: 2021/03/18 11:54:35 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*build_line_logic_pipe(t_list **token, int par)
{
	t_node *result;
	t_node *job;
	t_node *line;

	if ((job = build_job(token)) == NULL)
		return (NULL);
	if (!check(DPIPE, NULL, token))
	{
		ast_delete_node(job);
		return (NULL);
	}
	if ((line = build_line(token, par)) == NULL)
	{
		ast_delete_node(job);
		return (NULL);
	}
	if (!(result = create_node(NODE_LOGIC_PIPE, par ? "open" : NULL)))
		return (NULL);
	ast_attach_branch(result, job, line);
	return (result);
}

static t_node	*build_line_logic_amper(t_list **token, int par)
{
	t_node *result;
	t_node *job;
	t_node *line;

	if ((job = build_job(token)) == NULL)
		return (NULL);
	if (!check(DAMPERSTAND, NULL, token))
	{
		ast_delete_node(job);
		return (NULL);
	}
	if ((line = build_line(token, par)) == NULL)
	{
		ast_delete_node(job);
		return (NULL);
	}
	if (!(result = create_node(NODE_LOGIC_AMPERSTAND, par ? "open" : NULL)))
		return (NULL);
	ast_attach_branch(result, job, line);
	return (result);
}

static t_node	*build_line_semicolon(t_list **token, int par)
{
	t_node *result;
	t_node *job;
	t_node *line;

	if ((job = build_job(token)) == NULL)
		return (NULL);
	if (!check(SEMICOLON, NULL, token))
	{
		ast_delete_node(job);
		return (NULL);
	}
	if ((line = build_line(token, par)) == NULL)
	{
		ast_delete_node(job);
		return (NULL);
	}
	if (!(result = create_node(NODE_LINE, NULL)))
		return (NULL);
	ast_attach_branch(result, job, line);
	return (result);
}

static t_node	*build_line_semicolon_end(t_list **token)
{
	t_node *job;

	if ((job = build_job(token)) == NULL)
		return (NULL);
	if (!check(SEMICOLON, NULL, token))
	{
		ast_delete_node(job);
		return (NULL);
	}
	return (job);
}

t_node			*build_line(t_list **token, int par)
{
	t_node *node;
	t_list *save;

	par = check_par(OPEN_PAR, NULL, token);
	save = *token;
	if ((*token = save)
		&& (node = build_line_logic_pipe(token, par)))
		return (check_closing_par(par, token, node));
	if ((*token = save) &&
		(node = build_line_logic_amper(token, par)))
		return (check_closing_par(par, token, node));
	if ((*token = save)
		&& (node = build_line_semicolon(token, par)))
		return (check_closing_par(par, token, node));
	if ((*token = save)
		&& (node = build_line_semicolon_end(token)))
		return (check_closing_par(par, token, node));
	if ((*token = save)
		&& (node = build_line_job(token)))
		return (check_closing_par(par, token, node));
	return (NULL);
}
