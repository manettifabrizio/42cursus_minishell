/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:58:16 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/02 22:29:09 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_name(char **a, t_env *head, char *c)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(a[0], tmp->name) == 0)
		{
			// printf("%s\n%s\n", tmp->name, tmp->value);
			if (c && !(a[1]))
				tmp->value = "";
			else if (a[1])
				tmp->value = a[1];
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int		check_errors(char **a, char *s)
{
	int		x;

	x = -1;
	// Perchè è qui? Il controllo lo faccio già a riga 92
	// if (!(a[0]))
	// {
	// 	printf("* minish: export: `%s': not a valid identifier\n", s);
	// 	return (0);
	// }
	while (a[0][++x])
		if (!(ft_isalpha(a[0][x])))
		{
			printf("minish: export: `%s': not a valid identifier\n", s);
			return (0);
		}
	return (1);
}

static int		ft_export_var(char **a, t_env *head)
{
	int		x;
	t_env	*tmp;
	char	**cmd;

	x = 0;
	tmp = head;
	while (a[++x])
	{
		cmd = ms_split(a[x], '=');
		// ft_print_array(cmd);
		if (check_errors(cmd, a[x]))
			if (!(check_name(cmd, head, ft_strchr(a[x], '='))))
			{
				tmp = ft_lstnew_e();
				tmp->name = cmd[0];
				printf("cmd = %s\n", cmd[0]);
				if (cmd[1])
					tmp->value = cmd[1];
				ft_lstadd_back_e(&head, tmp);
				//free(cmd);
			}
	}
	return (0);
}

int		ft_export(char **a, t_env *head)
{
	char	**cmd;
	t_env	*l;
	t_env	*lhead;

	// printf ("---- head->name = %s\n ---- head->value = %s\n", head->name, head->value);
	// ms_print_list(head);
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
	else
		if (ft_export_var(a, head))
			return (1); //error
	return (1);
}