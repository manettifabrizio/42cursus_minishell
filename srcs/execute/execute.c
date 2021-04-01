/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/04/01 12:08:23 by fmanetti         ###   ########.fr       */
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
		malloc_error(m, NULL, NO_READING);
	if (!(builtins(m, builtin->data)))
		if (!(execute_bin(m)))
		{
			error(NO_ERRNO, "command not found");
			m->exit_status = 127;
		}
	ft_free_array(m->arr);
}

void			execute_command(t_main *m, t_node *command, int logic_type)
{
	int		tmp_in;
	int		tmp_out;

	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	if (!command)
		return ;
	if (command->type == NODE_REDIRECT_IN ||
		command->type == NODE_REDIRECT_OUT ||
		command->type == NODE_REDIRECT_OVER ||
		command->type == NODE_REDIRECT_HEREDOC)
	{
		if (handle_redirection(command))
		{
			dup2(tmp_in, STDIN_FILENO);
			dup2(tmp_out, STDOUT_FILENO);
			m->exit_status = 1;
			return ;
		}
		m->exit_status = 0;
		execute_builtin(m, command->left, logic_type);
		if (command->type == NODE_REDIRECT_HEREDOC)
			remove(".heredoc");
		dup2(tmp_in, STDIN_FILENO);
		dup2(tmp_out, STDOUT_FILENO);
	}
	else
		execute_builtin(m, command, logic_type);
	ft_signal(m->exit_status);
}

static void		execute_pipe(t_main *m, t_node *node_pipe, int logic_type)
{
	t_node	*job;
	t_std	std;

	init_std(&std);
	dup2(std.fd_out, STDOUT_FILENO);
	execute_builtin(m, node_pipe->left, logic_type);
	job = node_pipe->right;
	while (job->type == NODE_PIPE)
	{
		execute_inter_pipe(&std, m, job, logic_type);
		job = job->right;
	}
	dup2(std.fd_in, STDIN_FILENO);
	close(std.fd_out);
	dup2(std.tmp_out, STDOUT_FILENO);
	execute_command(m, job, logic_type);
	close(std.fd_in);
	dup2(std.tmp_out, STDOUT_FILENO);
	dup2(std.tmp_in, STDIN_FILENO);
}

static void		execute_job(t_main *m, t_node *job, int logic_type)
{
	if (!job)
		return ;
	if (job->type == NODE_PIPE)
		execute_pipe(m, job, logic_type);
	else
	{
		execute_command(m, job, logic_type);
	}
}

void			execute_command_line(t_main *m, t_node *cmd_line, int type)
{
	if (!cmd_line)
		return ;
	if (cmd_line->type == NODE_LOGIC_AMPERSTAND ||
		cmd_line->type == NODE_LOGIC_PIPE ||
		cmd_line->type == NODE_LINE)
	{
		execute_job(m, cmd_line->left, type);
		if (cmd_line->data && cmd_line->data[0] == 'o')
		{
			if ((type == NODE_LOGIC_AMPERSTAND && m->exit_status)
				|| (type == NODE_LOGIC_PIPE && !m->exit_status))
			{
				while (cmd_line)
				{
					if (cmd_line->data && cmd_line->data[0] == 'c')
						break ;
					cmd_line = cmd_line->right;
				}
			}
		}
		execute_command_line(m, cmd_line->right, cmd_line->type);
	}
	else
		execute_job(m, cmd_line, type);
}
