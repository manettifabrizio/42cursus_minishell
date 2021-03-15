/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:58:16 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/12 10:27:13 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_varname(char **cmd, t_list **head, char *c)
{
	t_list	*l;
	t_env	*tmp;

	l = *head;
	while (l)
	{
		tmp = t_access_env(l);
		if (ft_strcmp(cmd[0], tmp->name) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			if (c && !(cmd[1]))
				tmp->value = "";
			else if (cmd[1])
				tmp->value = cmd[1];
			return (1);
		}
		l = l->next;
	}
	return (0);
}

static int		check_errors(t_main *m, char *varname, char *s)
{
	int		x;

	x = -1;
	while (varname[++x])
		if (!(ft_isalpha(varname[x])))
		{
			printf("minish: %s: `%s': not a valid identifier\n", ERROR, s);
			m->exit_status = -1;
			return (0);
		}
	return (1);
}

static int		export_var(t_main *m, char **a, t_list **head)
{
	int		x;
	char	**cmd;

	x = 0;
	while (a[++x])
	{	// cmd non ha bisogno di essere free() perchè l'inidirizzo finisce in ehead
		cmd = split_exp(a[x], '=');
		if (check_errors(m, cmd[0], a[x]))
			if (!(check_varname(cmd, head, ft_strchr(a[x], '='))))
				ft_lstadd_back(head, create_env_elem(cmd));
	}
	return (1);
}

int		ft_export(t_main *m, char **a, t_list **head)
{
	t_list	*l;
	t_env	*tmp;
	t_list	*lhead;

	if (!(lhead = list_sort(head)))
		malloc_error(m, NULL, NO_READING);
	l = lhead;
	if (!(a[1]))
		while (l)
		{
			tmp = t_access_env(l);
			if (tmp->value)
				printf ("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			else
				printf ("declare -x %s\n", tmp->name);
			l = l->next;
		}
	else
		if (!(export_var(m, a, head)))
			malloc_error(m, NULL, NO_READING);
	m->exit_status = (m->exit_status == -1) ? 1 : 0;
	// free_list();
	return (1);
}