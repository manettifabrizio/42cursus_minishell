/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:40:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/02 11:57:10 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_elem(t_env *l, t_env *prev)
{
	prev->next = l->next;
	free(l->name);
	if (l->value)
		free(l->value);
}

static int		check_errors(t_main *m, char *s)
{
	if (!(ft_isalpha(s[0])))
		return (status_error(m, NO_ERRNO, 1, "not a valid identifier"));
	return (0);
}

int		ft_unset(t_main *m, char **a, t_env *head)
{
	int x;
	t_env	*l;
	t_env	*prev;

	x = 0;
	m->exit_status = 0;
	while (a[++x])
	{
		if (check_errors(m, a[x]))
			return (1);
		prev = head;
		l = head;
		while (l)
		{
			if (ft_strcmp(a[x], l->name) == 0)
				delete_elem(l, prev);
			prev = l;
			l = l->next;
		}
	}
	return (1);
}