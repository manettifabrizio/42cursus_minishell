/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/03/08 17:33:25 by viroques         ###   ########.fr       */
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
    execute_command(m, node_pipe->left);
    execute_command(m, node_pipe->right);
}

static void        execute_job(t_main *m, t_node *job)
{
    if (!job)
        return;
    if (job->type == NODE_PIPE)
        execute_pipe(m, job);
    else
        execute_command(m, job);
}

static void        execute_command_line(t_main *m, t_node *cmd_line)
{
    int tmp_in;
    int tmp_out;
    
    if (!cmd_line)
        return ;
    tmp_in = dup(0);
    tmp_out = dup(1);
    if (cmd_line->type == NODE_LINE)
    {
        execute_job(m, cmd_line->left);
        dup2(tmp_in, 0);
        dup2(tmp_out, 1);
        execute_command_line(m, cmd_line->right);
    }
    else
    {   
        execute_job(m, cmd_line);
        dup2(tmp_in, 0);
        dup2(tmp_out, 1);
    }
}

void     execute_ast_tree(t_main *m, t_node *exec_tree)
{
    execute_command_line(m, exec_tree);
}