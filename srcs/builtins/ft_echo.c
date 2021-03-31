/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:31:41 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/27 14:28:59 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_options(char **a, int x)
{
	int		i;

	while (a[x])
	{
		if (ft_strncmp(a[x], "-n", 2) != 0)
			return (x);
		i = 1;		
		while (a[x][++i])
			if (a[x][i] != 'n')
				return (x);
		x++;
	}
	return (x);
}

int				ft_echo(t_main *m, char **a)
{
	int x;

	if (!(a[1]))
		ft_putchar('\n');
	else
	{
		x = check_options(a, 1);
		while (a[x])
		{
			ft_putstr(a[x]);
			if (a[x + 1])
				ft_putchar(' ');
			x++;
		}
		if (ft_strcmp(a[1], "-n") != 0)
			ft_putchar('\n');
	}
	m->exit_status = 0;
	return (1);
}