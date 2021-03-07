/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:30:11 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/07 16:07:16 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*home_or_back(t_main *m, char *s, char *path)
{
	if (!(s) || ft_strcmp(path, "\0") == 0)
	{
		path = get_env(m->ehead, "HOME");
		if (!(path))
			status_error(m, NO_ERRNO, 1, "HOME is not set");
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		path = get_env(m->ehead, "OLDPWD");
		if (!(path))
			status_error(m, NO_ERRNO, 1, "OLDPWD not set");
	}
	return (path);
}

int				ft_cd(t_main *m, char *s)
{
	char	*path;
	char	buf[1024];

	if (s)
		path = check_vars(m, s, m->ehead, m->exit_status);
	if (!(s) || ft_strcmp(path, "\0") == 0 || ft_strcmp(path, "-") == 0)
		if (!(path = home_or_back(m, s, path)))
			return (1);
	if (chdir(path))
		return (status_error(m, ERRNO, 1, ""));
	if (!(path = getcwd(buf, 1024)))
		return (status_error(m, ERRNO, 0, " error retrieving current \
directory: getcwd: cannot access parent directories:"));
	if (s && ft_strcmp(s, ".") != 0)
		set_env(m->ehead, "OLDPWD", get_env(m->ehead, "PWD"));
	set_env(m->ehead, "PWD", path);
	m->exit_status = 0; // Deve essere alla fine visto che cd è soggetto alle variabili
	return (1);
}