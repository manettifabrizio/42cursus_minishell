/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:31:04 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/26 17:04:50 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(t_main *m)
{
	char	*pwd;
	char	buf[1024];

	if (!(pwd = getcwd(buf, 1024)))
		error(ERRNO, NULL);
	printf("%s\n", pwd);
	set_env(m->ehead, "PWD", pwd);
	m->exit_status = 0;
	return (1);
}