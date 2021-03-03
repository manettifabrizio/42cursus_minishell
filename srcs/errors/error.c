/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:46:05 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/02 20:28:40 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error(int errtype, char *message)
{
	if (errtype == ERRNO)
		printf("minish: %s: %s\n", ERROR, strerror(errno));
	if (errtype == NO_ERRNO)
		printf("minish: %s: %s\n", ERROR, message);
	return (1);
}

int		status_error(t_main *m, int errtype, int status, char *message)
{
	if (errtype == ERRNO)
		printf("minish: %s:%s %s\n", ERROR, message, strerror(errno));
	if (errtype == NO_ERRNO)
		printf("minish: %s: %s\n", ERROR, message);
	m->exit_status = status;
	return (1);
}