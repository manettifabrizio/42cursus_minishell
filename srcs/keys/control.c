/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:07:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/29 12:32:11 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		control_c(t_main *m, char *s)
{
	ft_putchar('\n');
	m->exit_status = 1;
	s[0] = '\0';
	return (1);
}

void	control_d(t_main *m)
{
	int	status;

	status = m->exit_status;
	set_term_cano(m->base_term);
	make_history(m->hist_path, m->hist);
	free_all(m);
	ft_putstr("exit\n");
	exit(status);
}