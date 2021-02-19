/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:37:43 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/17 18:08:23 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_path(t_main m, char **env)
{
	int		x;
	void	*dirstream;
	t_dir	*ds;
	char	*path;
	pid_t	pid;

	x = -1;
	while ((m.path)[++x])
	{
		dirstream = opendir((m.path)[x]);
		while ((ds = readdir(dirstream)))
			if (ft_strcmp(ds->d_name, (m.arr)[0]) == 0)
			{
				if ((pid = fork()) < 0)
					return (-1); //ERROR: fork failed
				// child process
				if (pid == 0)
				{
					path = ft_strjoin((m.path)[x], (m.arr)[0]);
					printf("n = %d\n", execve(path, m.arr, env));
					free (path);
				}
				waitpid(pid, NULL, 0);
				return (1);
			}
		closedir(dirstream);
	}
	return (0);
}