/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/04/06 15:53:21 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			execute_builtin(t_main *m, t_node *builtin, int logic_type)
{
	if (!builtin)
		return ;
	if ((logic_type == NODE_LOGIC_AMPERSTAND && m->exit_status)
		|| (logic_type == NODE_LOGIC_PIPE && !m->exit_status))
		return ;
	if (!(m->arr = create_cmd_table(builtin, m)))
		return ;
	if (m->arr[0] && !(builtins(m, m->arr[0])))
		if (!(execute_bin(m)))
		{
			error(NO_ERRNO, "command not found");
			m->exit_status = 127;
		}
	ft_free_array(m->arr);
}

void			execute_command(t_main *m, t_node *command, int logic_type)
{
	if (!command)
		return ;
	if (command->type == NODE_REDIRECT_IN ||
		command->type == NODE_REDIRECT_OUT ||
		command->type == NODE_REDIRECT_OVER ||
		command->type == NODE_REDIRECT_HEREDOC)
	{
		if (handle_redirection(command, m))
		{
			m->exit_status = 1;
			return ;
		}
		m->exit_status = 0;
		execute_builtin(m, command->left, logic_type);
		if (command->type == NODE_REDIRECT_HEREDOC)
			remove(".heredoc");
		if (!command->left)
			execute_command(m, command->right, logic_type);
	}
	else
		execute_builtin(m, command, logic_type);
}

static void		execute_pipe(t_main *m, t_node *node_pipe, int logic_type, t_std *std)
{
	t_node	*job;

	pipe(std->fd);
	std->fd_in = std->fd[0];
	std->fd_out = std->fd[1];
	dup2(std->fd_out, STDOUT_FILENO);
	execute_command(m, node_pipe->left, logic_type);
	job = node_pipe->right;
	while (job->type == NODE_PIPE)
	{
		execute_inter_pipe(std, m, job, logic_type);
		job = job->right;
	}
	dup2(std->fd_in, STDIN_FILENO);
	close(std->fd_out);
	dup2(std->tmp_out, STDOUT_FILENO);
	execute_command(m, job, logic_type);
	close(std->fd_in);
}

static void		execute_job(t_main *m, t_node *job, int logic_type)
{
	t_std	std;

	if (!job)
		return ;
	std.tmp_in = dup(STDIN_FILENO);
	std.tmp_out = dup(STDOUT_FILENO);
	if (job->type == NODE_PIPE)
		execute_pipe(m, job, logic_type, &std);
	else
		execute_command(m, job, logic_type);
	dup2(std.tmp_in, STDIN_FILENO);
	dup2(std.tmp_out, STDOUT_FILENO);
}

void			execute_command_line(t_main *m, t_node *cmd_line, int type)
{
	if (!cmd_line)
		return ;
	if (cmd_line->type == NODE_LOGIC_AMPERSTAND ||
		cmd_line->type == NODE_LOGIC_PIPE ||	
		cmd_line->type == NODE_LINE)
	{
		if (cmd_line->left && cmd_line->left->parenthese)
		{
			if ((type == NODE_LOGIC_PIPE && !m->exit_status))
				cmd_line = cmd_line->right;	
		}
			execute_job(m, cmd_line->left, type);
			execute_command_line(m, cmd_line->right, cmd_line->type);
	}
	else
		execute_job(m, cmd_line, type);
}
