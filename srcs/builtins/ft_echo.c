/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:31:41 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 12:11:25 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_echo(t_main *m, char **a, t_list **head)
{
	int x;

	x = 0;
	if (!(a[1]))
		ft_putchar('\n');
	else
	{
		if (ft_strcmp(a[1], "-n") == 0)
			x = 1;
		while (a[++x])
		{
			ft_putstr(check_vars(m, a[x], head, m->exit_status));
			if (a[x + 1])
				ft_putchar(' ');
		}
		if (ft_strcmp(a[1], "-n") != 0)
			ft_putchar('\n');
	}
	m->exit_status = 0;
	return (1);
}