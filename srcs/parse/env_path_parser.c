/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:23:03 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 18:21:54 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		**env_parser(t_list **head, char **env)
{
	int		x;
	char	**a;
	t_list	*tmp;

	x = -1;
	while (env[++x])
	{
		a = ft_split(env[x], '=');
		tmp = create_env_elem(a);
		if (x == 0)
			*head = tmp;
		else
			ft_lstadd_back(head, tmp);
	}
	return (head);
}

char		*get_env(t_list **head, char *name)
{
	t_list	*l;

	l = *head;
	while (l && ft_strcmp(t_access_env(l)->name, name) != 0)
		l = l->next;
	if (l)
		return (t_access_env(l)->value);
	else
		return (NULL);
}

void		set_env(t_list **head, char *name, char *value)
{
	t_list	*l;

	l = *head;
	while (l && ft_strcmp(t_access_env(l)->name, name) != 0)
		l = l->next;
	if (l)
	{
		free(t_access_env(l)->value);
		t_access_env(l)->value = ft_strdup(value);
	}
}

char			**path_parser(t_list **head)
{
	int		x;
	char	**path;

	x = -1;
	path = ft_split(get_env(head, "PATH"), ':');
	while (path[++x])
		path[x] = ft_strjoin_nl(path[x], "/");
	return (path);
}
