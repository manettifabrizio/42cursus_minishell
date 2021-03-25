/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:17:01 by viroques          #+#    #+#             */
/*   Updated: 2021/03/24 15:40:45 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		redirect_in(t_node *redirect)
{
	int		fdout;

	fdout = open(redirect->data, O_RDWR | O_CREAT | O_TRUNC, 0640);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

static void		redirect_out(t_node *redirect)
{
	int fdin;

	fdin = open(redirect->data, O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

static void		redirect_over(t_node *redirect)
{
	int fdout;

	fdout = open(redirect->data, O_RDWR | O_CREAT | O_APPEND, 0640);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

static void		redirect_heredoc(void)
{
	int fdin;

	fdin = open(".heredoc", O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void			handle_redirection(t_node *node_redirect)
{
	t_node	*redirect;

	redirect = node_redirect;
	while (redirect)
	{
		if (redirect->type == NODE_REDIRECT_IN)
			redirect_in(redirect);
		else if (redirect->type == NODE_REDIRECT_OUT)
			redirect_out(redirect);
		else if (redirect->type == NODE_REDIRECT_OVER)
			redirect_over(redirect);
		else if (redirect->type == NODE_REDIRECT_HEREDOC)
			redirect_heredoc();
		redirect = redirect->right;
	}
}
