/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/03/08 21:04:32 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void        execute_builtin(t_main *m, t_node *builtin)
{
    if (!(m->arr = create_cmd_table(builtin)))
		malloc_error(m, NULL, NO_READING);
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
    if (command->type == NODE_REDIRECT_IN || command->type == NODE_REDIRECT_OUT
        || command->type == NODE_REDIRECT_OVER)
    {
        handle_redirection(command);
        execute_builtin(m, command->left);
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

    tmp_in = dup(0);
    tmp_out = dup(1);
    pipe(fd);
    fd_in = fd[0];
    fd_out = fd[1];
    dup2(fd_out, 1);
    execute_builtin(m, node_pipe->left);
    job = node_pipe->right;
    while (job->type == NODE_PIPE)
    {
        close(fd_out);
        pipe(fd);
        fd_out = fd[1];
        dup2(fd_in, 0);
        dup2(fd_out, 1);
        close(fd_in);
        execute_builtin(m, job->left);
        fd_in = fd[0];
        job = job->right;
    }
    dup2(fd_in, 0);
    close(fd_out);
    dup2(tmp_out, 1);
    execute_command(m, job);
    dup2(tmp_out, 1);
    dup2(tmp_in, 0);
    close(fd_in);
    return ;
}

static void        execute_job(t_main *m, t_node *job)
{
    int tmp_out;

    tmp_out = dup(0);
    if (!job)
        return;
    if (job->type == NODE_PIPE)
        execute_pipe(m, job);
    else
    {
        execute_command(m, job);
        dup2(tmp_out, 1);
    }
}

static void        execute_command_line(t_main *m, t_node *cmd_line)
{
    if (!cmd_line)
        return ;
    if (cmd_line->type == NODE_LINE)
    {
        execute_job(m, cmd_line->left);
        execute_command_line(m, cmd_line->right);
    }
    else
    {   
        execute_job(m, cmd_line);
    }
}

void     execute_ast_tree(t_main *m, t_node *exec_tree)
{
    execute_command_line(m, exec_tree);
}