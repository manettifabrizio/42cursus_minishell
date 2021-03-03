/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:07:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/01 12:20:30 by fmanetti         ###   ########.fr       */
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

int		control_d(t_main *m)
{
	set_term(0, m->base_term);
	make_history(m->hist_path, m->hist);
	ft_putstr("exit\n");
	exit(EXIT_SUCCESS);
	return (1);
}