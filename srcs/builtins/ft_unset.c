/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:40:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/02 22:36:07 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_errors(char *s)
{
	int		x;

	x = -1;
	// if (!(a[1]))
	// {
	// 	printf("minish: export: `%s': not a valid identifier\n", a[x]);
	// 	return (0);
	// }
	while (s[++x])
		if (!(ft_isalpha(s[x])))
		{
			printf("minish: export: `%s': not a valid identifier\n", s);
			return (0);
		}
	return (1);
}

int		ft_unset(char **a, t_env *head)
{
	int x;
	t_env	*l;
	t_env	*prev;

	x = 0;
	while (a[++x])
	{
		check_errors(a[x]);
		prev = head;
		l = head;
		while (l)
		{
			// printf("a[x] = %s\nl->name = %s\n", a[x], l->name);
			// printf ("ciaasdasdasdaos\n");
			if (ft_strcmp(a[x], l->name) == 0)
			{
				prev->next = l->next;
				free(l->name);
				if (l->value)
					free(l->value);
			}
			prev = l;
			l = l->next;
		}
	}
	return (1);
}