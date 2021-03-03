/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:56:35 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/03 22:35:56 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				builtins(t_main *m)
{
	if (ft_strcmp((m->arr)[0], "echo") == 0)
		return (ft_echo(m, m->arr, m->ehead));
	else if (ft_strcmp((m->arr)[0], "cd") == 0) // absolut path or relative
		return (ft_cd(m, (m->arr)[1]));
	else if (ft_strcmp((m->arr)[0], "pwd") == 0)
		return (ft_pwd(m, m->ehead));
	else if (ft_strcmp((m->arr)[0], "export") == 0)
		return (ft_export(m, m->arr, m->ehead));
	else if (ft_strcmp((m->arr)[0], "unset") == 0)
		return (ft_unset(m, m->arr, m->ehead));
	else if (ft_strcmp((m->arr)[0], "env") == 0)
		return (ft_env(m, m->ehead));
	else if (ft_strcmp((m->arr)[0], "exit") == 0)
		return (ft_exit(m, m->arr));
	return (0);
}