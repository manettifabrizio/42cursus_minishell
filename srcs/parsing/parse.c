/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:27:27 by fmanetti          #+#    #+#             */
/*   Updated: 2021/01/28 21:10:03 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		env_parser(t_main *m, char **env)
{
	int		x;
	char	**a;
	t_env	*tmp;

	x = 0;
	// printf("%s\n", "ciao1");
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
		x++;
	}
}

char			**path_parser(t_env *head)
{
	t_env	*tmp;
	char	**path;

	tmp = head;
	while (ft_strcmp(tmp->name, "PATH") != 0 && tmp != NULL)
		tmp = tmp->next;
	path = ft_split(tmp->value, ':');
	return (path);
}

void			line_parse(t_main *m, char **env)
{
	env_parser(m, env); 
	m->path = path_parser(m->ehead);
}