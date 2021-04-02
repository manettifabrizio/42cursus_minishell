/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:18:41 by viroques          #+#    #+#             */
/*   Updated: 2021/04/02 12:33:53 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**remove_empty_tab(char **tab, t_main *m)
{
	int		i;
	int		nb;
	char	**new;

	i = 0;
	nb = 0;
	while(tab[i])
	{
		if (tab[i][0] != '\0')
			nb++;
		i++;
	}
	if (!(new = malloc(sizeof(char *) * (nb + 1))))
		malloc_error(m, NULL, NO_ERRNO);
	i = 0;
	nb = 0;
	while (tab[i])
	{
		if (tab[i][0] != '\0')
		{
			new[nb] = ft_strdup(tab[i]);
			nb++;
		}
		i++;
	}
	new[nb] = NULL;
	ft_free_array(tab);
	return (new);
}

char			**check_empty_case(char **tab, t_main *m)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '\0')
			return (remove_empty_tab(tab, m));
		i++;
	}
	return (tab);
}

char			**create_cmd_table(t_node *root, t_main *m)
{
	t_node	*node;
	char	**args;
	int		nbcmd;

	nbcmd = 0;
	node = root;
	while (node)
	{
		nbcmd++;
		node = node->left;
	}
	if (!(args = malloc(sizeof(char *) * (nbcmd + 1))))
		return (NULL);
	node = root;
	nbcmd = 0;
	while (node)
	{
		args[nbcmd] = change_data(node->data, m);
		node = node->left;
		nbcmd++;
	}
	args[nbcmd] = NULL;
	return (check_empty_case(args, m));
}

static int		check_dir_and_absolute(t_main *m, char *path)
{
	DIR		*dir;
	int		fd;

	if ((dir = opendir(path)))
	{
		error(NO_ERRNO, "is a directory");
		m->exit_status = 126;
		return (1);
	}
	if (path[0] == '/' || path[0] == '.')
	{
		if ((fd = open(path, O_RDONLY)) == -1)
		{
			error(ERRNO, NULL);
			m->exit_status = 127;
			return (1);
		}
		close(fd);
	}
	return (0);
}

int				execute_bin(t_main *m)
{
	char	*path;
	pid_t	pid;
  
	if (check_dir_and_absolute(m, m->arr[0]))
		return (-1);
	if (!(path = search_path(m->arr[0], m->pathdirs)))
		return (0);
	if (path)
	{
		if ((pid = fork()) < 0)
			return (0);
		if (pid == 0)
		{
			if ((execve(path, m->arr, m->env)) == -1)
				return (0);
			return (1);
		}
		else
			m->exit_status = exit_status(pid);
		if (path)
			free(path);
		return (1);
	}
	return (0);
}
