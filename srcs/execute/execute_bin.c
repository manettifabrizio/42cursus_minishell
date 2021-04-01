/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:18:41 by viroques          #+#    #+#             */
/*   Updated: 2021/04/01 11:18:33 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*sort_backslash(char *str, t_main *m)
{
	int		i;
	char	*new;
	int		j;

	if (!(new = malloc(sizeof(char) * ft_strlen(str) + 1)))
		malloc_error(m, NULL, NO_READING);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		new[j] = str[i];
		j++;
		if (str[i])
			i++;
	}
	new[j] = '\0';
	return(new);
}

char			*add_quote(char *str, int *i, t_main *m)
{
	int		start;
	char	*sub;
	char	*var;
	char	*backslash;

	start = *i;
	while (str[*i])
	{
		if (str[*i] == '\\')
		{
			if (str[*i + 1] && str[*i + 1] == '\"')
			*i += 1;
		}
		else if (str[*i] == '\"')
		{
			*i += 1;
			break;
		}
		*i += 1;
	}
	sub = ft_substr(str, start, *i - start - 1);
	var = check_vars(m, sub, m->ehead, m->exit_status);
	backslash = sort_backslash(var, m);
	free(sub);
	free(var);
	return (backslash);
}

char			*add_squote(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i])
	{
		if (str[*i] == '\\')
		{
			if (str[*i + 1] && str[*i + 1] == '\'')
			*i += 1;
		}
		else if (str[*i] == '\'')
		{
			*i += 1;
			break;
		}
		*i += 1;
	}
	return (ft_substr(str, start, *i - start - 1));
}

char			*add_w(char *str, int *i, t_main *m)
{
	int 	start;
	char	*sub;
	char	*var;
	char	*backslash;

	start = *i;
	while (str[*i])
	{
		if (str[*i] == '\\')
		{
			if (str[*i + 1] && (str[*i + 1] == '\''
				|| str[*i + 1 == '\"']))
			*i += 1;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			break;
		*i += 1;
	}
	sub = ft_substr(str, start, *i - start);
	var = check_vars(m, sub, m->ehead, m->exit_status);
	backslash = sort_backslash(var, m);
	free(sub);
	free(var);
	return (backslash);
}

char			*change_data(char *str, t_main *m)
{
	int i;
	char *data;
	char *tmp;
	char *add;

	data = malloc(sizeof(char));
	*data = '\0';
	i =  0;
	while ((size_t)i < ft_strlen(str))
	{
		if (str[i] && str[i] == '\"')
		{
			i++;
			tmp = data;
			add = add_quote(str, &i, m);
			data = ft_strjoin(tmp, add);
			free(tmp);
			free(add);
		}
		else if (str[i] == '\'')
		{
			i++;
			tmp = data;
			add = add_squote(str, &i);
			data = ft_strjoin(tmp, add);
			free(tmp);
			free(add);
		}
		else
		{
			tmp = data;
			add = add_w(str, &i, m);
			data = ft_strjoin(tmp, add);
			free(add);
			free(tmp);
		}
	}
	return (data);
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
	return (args);
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
