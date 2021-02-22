/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:07:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/22 22:09:01 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		control_c(char *s)
{
	ft_putchar('\n');
	s[0] = '\0';
	return (1);
}

int		control_d(struct termios *base_term)
{
	set_term(0, base_term);
	ft_putstr("exit\n");
	exit(EXIT_SUCCESS);
	return (1);
}