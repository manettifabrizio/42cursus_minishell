/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:46:05 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 17:38:14 by viroques         ###   ########.fr       */
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
	if (errtype == READING)
	{
		printf("minish: %s: %s\n", ERROR, strerror(errno));
		free(s);
	}
	else if (errtype == NO_READING)
		printf("minish: %s: %s\n", ERROR, strerror(errno));
	m->exit_status = 1;
	// free_all()
	// ft_exit();
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