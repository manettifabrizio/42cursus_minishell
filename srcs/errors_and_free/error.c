/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:46:05 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 20:09:47 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error(int errtype, char *message)
{
	if (errtype == ERRNO)
		printf("minish: %s: %s\n", ERROR, strerror(errno));
	else if (errtype == NO_ERRNO)
		printf("minish: %s: %s\n", ERROR, message);
	return (1);
}

int		status_error(t_main *m, int errtype, int status, char *message)
{
	if (errtype == ERRNO)
		printf("minish: %s:%s %s\n", ERROR, message, strerror(errno));
	else if (errtype == NO_ERRNO)
		printf("minish: %s: %s\n", ERROR, message);
	m->exit_status = status;
	return (1);
}

void		malloc_error(t_main *m, char *s, int errtype)
{
	int		status;

	if (errtype == READING)
	{
		printf("minish: %s: %s\n", ERROR, strerror(errno));
		free(s);
	}
	else if (errtype == NO_READING)
		printf("minish: %s: %s\n", ERROR, strerror(errno));
	status = 1;
	free_all(m);
	exit(status);
}

int		malloc_error_1(t_main *m)
{
	printf("minish: %s: %s\n", ERROR, strerror(errno));
	m->exit_status = 1;
	return (-1);
}

char		*malloc_error_2(t_main *m)
{
	printf("minish: %s: %s\n", ERROR, strerror(errno));
	m->exit_status = 1;
	return (NULL);
}