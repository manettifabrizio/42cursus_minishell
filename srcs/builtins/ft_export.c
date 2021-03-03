/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:58:16 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/02 20:00:32 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_name(char **cmd, t_env *head, char *c)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
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
		tmp = tmp->next;
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

static int		export_var(t_main *m, char **a, t_env *head)
{
	int		x;
	t_env	*tmp;
	char	**cmd;

	x = 0;
	tmp = head;
	while (a[++x])
	{	// cmd non ha bisogno di essere free() perchè l'inidirizzo finisce in ehead
		cmd = ms_split_exp(a[x], '=');
		if (cmd[1])
			cmd[1] = check_vars(cmd[1], head, m->exit_status);
		if (check_errors(m, cmd[0], a[x]))
			if (!(check_name(cmd, head, ft_strchr(a[x], '='))))
			{
				tmp = ft_lstnew_e();
				tmp->name = cmd[0];
				if (cmd[1])
					tmp->value = cmd[1];
				ft_lstadd_back_e(&head, tmp);
			}
	}
	return (0);
}

int		ft_export(t_main *m, char **a, t_env *head)
{
	t_env	*l;
	t_env	*lhead;

	lhead = ms_list_sort(head);
	l = lhead;
	if (!(a[1]))
		while (l)
		{
			if (l->value)
				printf ("declare -x %s=\"%s\"\n", l->name, l->value);
			else
				printf ("declare -x %s\n", l->name);
			l = l->next;
		}
	else // a deve arrivare con le variabili già separate e divise nell'array
		if (export_var(m, a, head))
			return (1);
	m->exit_status = (m->exit_status == -1) ? 1 : 0;
	return (1);
}