/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:17:01 by viroques          #+#    #+#             */
/*   Updated: 2021/03/31 17:49:20 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_out(t_node *redirect)
{
	int		fdout;

	if ((fdout = open(redirect->data, O_RDWR | O_CREAT | O_TRUNC, 0640)) == -1)
	{
		error(ERRNO, NULL);
		return (1);
	}
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return (0);
}

static int		redirect_in(t_node *redirect)
{
	int fdin;

	if ((fdin = open(redirect->data, O_RDONLY)) == -1)
	{
		error(ERRNO, NULL);
		return (1);
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (0);
}

static int	redirect_over(t_node *redirect)
{
	int fdout;

	if ((fdout = open(redirect->data, O_RDWR | O_CREAT | O_APPEND, 0640)) == -1)
	{
		error(ERRNO, NULL);
		return (1);
	}
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return (0);
}

static int	redirect_heredoc(void)
{
	int fdin;

	if ((fdin = open(".heredoc", O_RDONLY)) == -1)
	{
		error(ERRNO, NULL);
		return (1);
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (0);
}

int				handle_redirection(t_node *node_redirect)
{
	t_node	*redirect;
	int		ret;

	ret = 0;
	redirect = node_redirect;
	while (redirect)
	{
		if (redirect->type == NODE_REDIRECT_IN)
			ret = redirect_in(redirect);
		else if (redirect->type == NODE_REDIRECT_OUT)
			ret = redirect_out(redirect);
		else if (redirect->type == NODE_REDIRECT_OVER)
			ret = redirect_over(redirect);
		else if (redirect->type == NODE_REDIRECT_HEREDOC)
			ret = redirect_heredoc();
		if (ret)
			return (ret);
		redirect = redirect->right;
	}
	return (0);
}
