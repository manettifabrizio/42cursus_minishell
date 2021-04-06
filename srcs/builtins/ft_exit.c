/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:29:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/06 16:46:43 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		the_end(t_main *m, int status)
{
	set_term_cano(m->base_term);
	make_history(m->hist_path, m->hist);
	free_all(m);
	ft_putstr("exit\n");
	exit(status);
}

int				ft_exit(t_main *m, char **a)
{
	int		i;
	int		status;

	if (!(a[1]))
		status = m->exit_status;
	else
	{
		status = ft_atoi(a[1]);
		i = -1;
		while (a[1][++i])
			if ((ft_isdigit(a[1][i]) == 0 && a[1][i] != '-' && a[1][i] != '+')
				|| ((a[1][i] == '-' || a[1][i] == '+') && !a[1][i + 1]))
			{
				error(NO_ERRNO, "numeric argument required");
				status = 255;
				the_end(m, status);
			}
		if (a[2])
			return (status_error(m, NO_ERRNO, 1, "too many arguments"));
	}
	the_end(m, status);
	return (1);
}