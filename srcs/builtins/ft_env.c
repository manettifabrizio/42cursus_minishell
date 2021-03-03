/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:28:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/02 16:52:44 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_main *m, t_env *head)
{
	t_env	*l;

	l = head;
	m->exit_status = 0;
	while (l != NULL)
	{
		if (l->value)
			printf("%s=%s\n", l->name, l->value);
		l = l->next;
	}
	return (1);
}