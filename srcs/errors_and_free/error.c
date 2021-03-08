/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:46:05 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 19:20:37 by fmanetti         ###   ########.fr       */
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

int     error_parsing(char *data)
{
    char *error;

    error = ft_strjoin("Syntax error near: ", data);
    write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    free(error);
    return (-1);
}