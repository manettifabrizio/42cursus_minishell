/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:31:41 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/12 09:49:36 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_echo(t_main *m, char **a, t_list **head)
{
	int x;
	(void)head;
	x = 0;
	if (!(a[1]))
		ft_putchar('\n');
	else
	{
		if (ft_strcmp(a[1], "-n") == 0)
			x = 1;
		while (a[++x])
		{
			ft_putstr(a[x]);
			if (a[x + 1])
				ft_putchar(' ');
		}
		if (ft_strcmp(a[1], "-n") != 0)
			ft_putchar('\n');
	}
	m->exit_status = 0;
	return (1);
}