/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:37:43 by fmanetti          #+#    #+#             */
/*   Updated: 2021/01/29 16:24:15 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_path(char **a, char *s)
{
	int 	x;
	char	**path;

	x = 0;
	while (a[x] != NULL)
		x++;
	if (!(path = malloc(++x * sizeof(char*))))
		return (NULL); //exit error
	x = 0;
	// printf("a = %s\n", a[x]);
	while (a[x] != NULL)
	{
		// printf("a = %s\n", a[x]);
		if (!(path[x] = malloc((ft_strlen(a[x]) + 1) * sizeof(char))))
			return (NULL); //exit error
		path[x] = ft_strjoin(a[x], "/");
		x++;
	}
	path[x] = NULL;
	// free(a);
	return (path);
}

int		search_path(t_main m, char **env)
{
	int		x;
	void	*dirp;
	t_dir	*ds;
	char	**b;
	char	*path;

	x = 0;
	b = malloc(2 * sizeof(char*));
	b[0] = m.str;
	b[1] = NULL;
	m.path = create_path(m.path, m.str);
	// m.path[0] = "/usr/bin/vim";
	while ((m.path)[x] != NULL)
	{
		dirp = opendir((m.path)[x]);
		while ((ds = readdir(dirp)))
			if (ft_strcmp(ds->d_name, m.str) == 0)
			{
				path = ft_strjoin((m.path)[x], m.str);
				printf("n = %d\n", execve(path, b, env));
				free (path);
				return (1);
			}
		closedir(dirp);
		x++;
	}
	return (0);
}