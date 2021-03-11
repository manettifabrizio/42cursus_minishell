/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/03/11 20:33:46 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void        execute_builtin(t_main *m, t_node *builtin)
{
    if (!(m->arr = create_cmd_table(builtin)))
		malloc_error(m, NULL, NO_READING);
	ft_print_array(m->arr, "cmd_table");
    if (!(builtins(m, builtin->data)))
        if (!(execute_bin(m, builtin)))
		{
			error(NO_ERRNO, "command not found");
			m->exit_status = 127;
		}
}

static void        execute_command(t_main *m, t_node *command)
{
    if (!command)
        return;
    if (command->type == NODE_REDIRECT_IN || 
		command->type == NODE_REDIRECT_OUT ||
		command->type == NODE_REDIRECT_OVER || 
		command->type == NODE_REDIRECT_HEREDOC)
    {
        handle_redirection(command);
        execute_builtin(m, command->left);
		if (command->type == NODE_REDIRECT_HEREDOC)
			remove(".heredoc");
    }
    else
        execute_builtin(m, command);
}

static void        execute_pipe(t_main *m, t_node *node_pipe)
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
    execute_builtin(m, node_pipe->left);
    job = node_pipe->right;
    while (job->type == NODE_PIPE)
    {
        close(fd_out);
        fd_in = fd[0];
        pipe(fd);
        fd_out = fd[1];
        dup2(fd_in, STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        execute_builtin(m, job->left);
        close(fd_in);
        fd_in = fd[0];
        job = job->right;
    }
    dup2(fd_in, STDIN_FILENO);
    close(fd_out);
    dup2(tmp_out, STDOUT_FILENO);
    execute_command(m, job);
    close(fd_in);
    dup2(tmp_out, STDOUT_FILENO);
    dup2(tmp_in, STDIN_FILENO);
    return ;
}

static void        execute_job(t_main *m, t_node *job)
{

    if (!job)
        return;
    if (job->type == NODE_PIPE)
        execute_pipe(m, job);
    else
    {
        execute_command(m, job);
    }
}

static void        execute_command_line(t_main *m, t_node *cmd_line)
{
    int tmp_in;
    int tmp_out;

    tmp_in = dup(STDIN_FILENO);
    tmp_out = dup(STDOUT_FILENO);
    if (!cmd_line)
        return ;
    if (cmd_line->type == NODE_LINE)
    {
        execute_job(m, cmd_line->left);
        dup2(tmp_in, STDIN_FILENO);
        dup2(tmp_out, STDOUT_FILENO);
        execute_command_line(m, cmd_line->right);
    }
    else
    {   
        execute_job(m, cmd_line);
        dup2(tmp_in, STDIN_FILENO);
        dup2(tmp_out, STDOUT_FILENO);
    }
}

void     execute_ast_tree(t_main *m, t_node *exec_tree)
{
    execute_command_line(m, exec_tree);
}