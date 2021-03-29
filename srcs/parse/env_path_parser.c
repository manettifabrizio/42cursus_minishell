/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:23:03 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/26 15:40:29 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*create_env_elem(char **a, char *equal)
{
	t_env	*l;
	t_list	*tmp;

	if (!(l = malloc(sizeof(t_env))))
		return (0);
	l->name = a[0];
	if (equal && !(a[1]))
		l->value = ft_strdup("");
	else if (a[1])
		l->value = a[1];
	else
		l->value = NULL;
	if (!(tmp = ft_lstnew(l)))
		return (0);
	return (tmp);
}

t_list		**env_parser(t_list **head, char **env)
{
	int		x; //segfault se c'è un  problema
	char	**a;
	t_list	*tmp;

	x = -1;
	while (env[++x])
	{
		a = ft_split(env[x], '=');
		tmp = create_env_elem(a, ft_strchr(env[x], '='));
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
