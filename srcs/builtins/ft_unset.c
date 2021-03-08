/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:40:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 18:03:06 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_elem(t_list *l, t_list *prev)
{
	t_env	*tmp;

	tmp = t_access_env(l);
	prev->next = l->next;
	free(tmp->name);
	if (tmp->value)
		free(tmp->value);
}

static int		check_errors(t_main *m, char *s)
{
	if (!(ft_isalpha(s[0])))
		return (status_error(m, NO_ERRNO, 1, "not a valid identifier"));
	return (0);
}

int		ft_unset(t_main *m, char **a, t_list **head)
{
	int x;
	t_list	*l;
	t_list	*prev;

	x = 0;
	m->exit_status = 0;
	while (a[++x])
	{
		if (check_errors(m, a[x]))
			return (1);
		l = *head;
		prev = *head;
		while (l)
		{
			if (ft_strcmp(a[x], t_access_env(l)->name) == 0)
				delete_elem(l, prev);
			prev = l;
			l = l->next;
		}
	}
	return (1);
}