/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/03/18 16:31:00 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execute_builtin(t_main *m, t_node *builtin, int logic_type)
{
	if ((logic_type == NODE_LOGIC_AMPERSTAND && m->exit_status)
		|| (logic_type == NODE_LOGIC_PIPE && !m->exit_status))
		return ;
	if (!(m->arr = create_cmd_table(builtin)))
		malloc_error(m, NULL, NO_READING);
	if (!(builtins(m, builtin->data)))
		if (!(execute_bin(m, builtin)))
		{
			error(NO_ERRNO, "command not found");
			m->exit_status = 127;
		}
}

static void		execute_command(t_main *m, t_node *command, int logic_type)
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
		handle_redirection(command);
		execute_builtin(m, command->left, logic_type);
		if (command->type == NODE_REDIRECT_HEREDOC)
			remove(".heredoc");
		dup2(tmp_in, STDOUT_FILENO);
		dup2(tmp_out, STDOUT_FILENO);
	}
	else
		execute_builtin(m, command, logic_type);
}

static void		execute_pipe(t_main *m, t_node *node_pipe, int logic_type)
{
	int     fd[2];
	int     tmp_in;
	int     tmp_out;
	t_node  *job;
	int     fd_in;
	int     fd_out;

	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	pipe(fd);
	fd_in = fd[0];
	fd_out = fd[1];
	dup2(fd_out, STDOUT_FILENO);
	execute_builtin(m, node_pipe->left, logic_type);
	job = node_pipe->right;
	while (job->type == NODE_PIPE)
	{
		close(fd_out);
		fd_in = fd[0];
		pipe(fd);
		fd_out = fd[1];
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execute_builtin(m, job->left, logic_type);
		close(fd_in);
		fd_in = fd[0];
		job = job->right;
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_out);
	dup2(tmp_out, STDOUT_FILENO);
	execute_command(m, job, logic_type);
	close(fd_in);
	dup2(tmp_out, STDOUT_FILENO);
	dup2(tmp_in, STDIN_FILENO);
	return ;
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

static void		execute_command_line(t_main *m, t_node *cmd_line, int type)
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

void		execute_ast_tree(t_main *m, t_node *exec_tree)
{
	execute_command_line(m, exec_tree, 0);
}
