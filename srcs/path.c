/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:37:43 by fmanetti          #+#    #+#             */
/*   Updated: 2021/01/30 19:21:28 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_path(t_main m, char **env)
{
	int		x;
	void	*dirp;
	t_dir	*ds;
	char	**b;
	char	*path;
	pid_t	pid;

	x = 0;
	b = malloc(2 * sizeof(char*));
	b[0] = (m.arr)[0];
	b[1] = NULL;
	// m.path[0] = "/usr/bin/vim";
	while ((m.path)[x] != NULL)
	{
		dirp = opendir((m.path)[x]);
		while ((ds = readdir(dirp)))
			if (ft_strcmp(ds->d_name, (m.arr)[0]) == 0)
			{
				if ((pid = fork()) < 0)
					return (-1); //ERROR: fork failed
				// child process
				if (pid == 0)
				{
					path = ft_strjoin((m.path)[x], (m.arr)[0]);
					printf("n = %d\n", execve(path, b, env));
					free (path);
				}
				waitpid(pid, NULL, 0);
				return (1);
			}
		closedir(dirp);
		x++;
	}
	return (0);
}