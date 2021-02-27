/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:27:27 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/27 20:04:14 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		env_parser(t_main *m, char **env)
{
	int		x;
	char	**a;
	t_env	*tmp;

	x = 0;
	while (env[x] != NULL)
	{
		tmp = ft_lstnew_e();
		if (x == 0)
			m->ehead = tmp;
		a = ft_split(env[x], '=');
		tmp->name = a[0];
		// printf("%s=", tmp->name);
		tmp->value = a[1];
		// printf("%s\n", tmp->value);
		ft_lstadd_back_e(&(m->ehead), tmp);
		//free_array
		x++;
	}
}

static char	**add_slash(char **a)
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

char			**path_parser(t_env *head)
{
	t_env	*tmp;
	char	**path;

	tmp = head;
	while (ft_strcmp(tmp->name, "PATH") != 0 && tmp != NULL)
		tmp = tmp->next;
	path = ft_split(tmp->value, ':');
	path = add_slash(path);
	return (path);
}

void			shell_parse(t_main *m, char **env)
{
	// env = ft_sort_array(env);
	env_parser(m, env);
	m->path = path_parser(m->ehead);
}