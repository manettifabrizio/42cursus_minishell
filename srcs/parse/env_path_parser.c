/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:23:03 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/03 20:02:09 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*env_parser(t_env *head, char **env)
{
	int		x;
	char	**a;
	t_env	*tmp;

	x = -1;
	while (env[++x])
	{
		tmp = ft_lstnew_e();
		if (x == 0)
			head = tmp;
		a = ft_split(env[x], '=');
		tmp->name = a[0];
		tmp->value = a[1];
		ft_lstadd_back_e(&(head), tmp);
	}
	return (head);
}

char		*get_env(t_env *head, char *name)
{
	t_env	*tmp;

	tmp = head;
	while (tmp && ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	if (tmp)
		return (tmp->value);
	else
		return (NULL);
}

void		set_env(t_env *head, char *name, char *value)
{
	t_env	*tmp;

	tmp = head;
	while (tmp && ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
	}
}

char			**path_parser(t_env *head)
{
	int		x;
	char	**path;

	x = -1;
	path = ft_split(get_env(head, "PATH"), ':');
	while (path[++x])
		path[x] = ft_strjoin_nl(path[x], "/");
	return (path);
}
