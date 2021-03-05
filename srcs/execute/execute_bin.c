/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:18:41 by viroques          #+#    #+#             */
/*   Updated: 2021/03/05 13:51:35 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char        **create_cmd_table(t_node *root)
{
    t_node  *node;
    char    **args;
    int     nbcmd;

    nbcmd = 0;
    node = root;
    while(node)
    {
        nbcmd++;
        node = node->left;
    }
    args = malloc(sizeof(char *) * (nbcmd + 1));
    node = root;
    nbcmd = 0;
    while (node)
    {
        args[nbcmd] = ft_strdup(node->data);
        node = node->left;
        nbcmd++;
    }
    args[nbcmd] = NULL;
    return (args);
}

int		exit_signals(int signal)
{
	if (signal == SIGINT)
		return (130);
	else if (signal == SIGQUIT)
		return (131);
	else if (signal == SIGTSTP)
		return (146);
	return (0);
}

int		exit_status(pid_t pid)
{
	int		ret;
	int		status;

	ret = waitpid(pid, &status, 0);
	if (ret < 0)
		printf("Failed to wait for process %d (errno = %d)\n", (int)pid, errno); //error
	else if (ret != pid) // devono essere uguali
		printf("Got ret of process %d (status 0x%.4X) when expecting PID %d\n", ret, status, (int)pid);
	else if (WIFEXITED(status)) // ritorna vero se il child è uscito normalmente
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (exit_signals(WTERMSIG(status)));
	else
		return (-1); //error
	return (1);
}

int     execute_bin(t_main *m, t_node *cmd, t_flux *flux)
{
    char **args;
    char *path;
    pid_t pid;
    
    if ((pid = fork()) < 0)
        return (-1);
    if (pid == 0)
    {   
        if (cmd->data[0] == '/')
            path = cmd->data;
        else
        	path = search_path(cmd->data, m->pathdirs);
        args = create_cmd_table(cmd);
        handle_piping(flux);
        if ((execve(path, args, m->env)) == -1)
        {
            write(2, strerror(errno), ft_strlen(strerror(errno)));
            write(2, "\n", 1);
        }
        ft_free_array(args);
    }
	else
		m->exit_status = exit_status(pid);
    return (1);
}