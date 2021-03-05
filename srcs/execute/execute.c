/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/03/05 19:31:46 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void        execute_builtin(t_main *m, t_node *builtin, t_flux *flux)
{
    m->arr = create_cmd_table(builtin);
    if ((builtins(m, builtin->data)));
    else
        execute_bin(m, builtin, flux);
}

static void        execute_command(t_main *m, t_node *command, t_flux *flux)
{
    if (!command)
        return;
    if (command->type == NODE_REDIRECT_IN || command->type == NODE_REDIRECT_OUT
        || command->type == NODE_REDIRECT_OVER)
    {
        handle_redirection(command);
        execute_builtin(m, command->left, flux);
    }
    else
        execute_builtin(m, command, flux);
}

static void        execute_pipe(t_main *m, t_node *node_pipe, t_flux *flux)
{
    int     fd[2];
    t_node  *job;
    
    pipe(fd);
    set_pipe_bool(0, 1, fd, flux);
    execute_command(m, node_pipe->left, flux);
    job = node_pipe->right;
    while (job && job->type == NODE_PIPE)
    {
        set_pipe_bool(1, 1, fd, flux);
        close(flux->pipe_write);
        pipe(fd);
        flux->pipe_write = fd[1];
        execute_command(m, job->left, flux);
        close(flux->pipe_read);
        flux->pipe_read= fd[0];
        job = job->right;
    }
    set_pipe_bool(1, 0, fd, flux);
    execute_command(m, job, flux);
    close(flux->pipe_read);
}

static void        execute_job(t_main *m, t_node *job, t_flux *flux)
{
    if (!job)
        return;
    if (job->type == NODE_PIPE)
    {
        execute_pipe(m, job, flux);
    }
    else
        execute_command(m, job, flux);
}

static void        execute_command_line(t_main *m, t_node *cmd_line, t_flux *flux)
{
    int tmp_in;
    int tmp_out;
    
    if (!cmd_line)
        return ;
    tmp_in = dup(0);
    tmp_out = dup(1);
    if (cmd_line->type == NODE_LINE)
    {
        execute_job(m, cmd_line->left, flux);
        dup2(tmp_in, 0);
        dup2(tmp_out, 1);
        execute_command_line(m, cmd_line->right, flux);
    }
    else
    {   
        execute_job(m, cmd_line, flux);
        dup2(tmp_in, 0);
        dup2(tmp_out, 1);
    }
}

void     execute_ast_tree(t_main *m, t_node *exec_tree)
{
    t_flux      flux;

	ft_bzero(&flux, sizeof(t_flux));
    execute_command_line(m, exec_tree, &flux);
}