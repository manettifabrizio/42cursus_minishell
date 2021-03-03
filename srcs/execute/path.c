/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:37:43 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/03 20:40:12 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		search_path(t_main *m, char **env)
{
	int		x;
	void	*dirstream;
	t_dir	*ds;
	char	*path;
	pid_t	pid;

	x = -1;
	while ((m->path)[++x])
	{
		dirstream = opendir((m->path)[x]);
		while ((ds = readdir(dirstream)))
			// Search command with readdir
			if (ft_strcmp(ds->d_name, (m->arr)[0]) == 0)
			{
				if ((pid = fork()) < 0)
					return (-1); //ERROR: fork failed
				// child process
				if (pid == 0)
				{
					path = ft_strjoin((m->path)[x], (m->arr)[0]);
					execve(path, m->arr, env);
					free(path);
				}
				m->exit_status = exit_status(pid);
				return (1);
			}
		closedir(dirstream);
	}
	return (0);
}