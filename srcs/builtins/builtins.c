/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:56:35 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 18:24:48 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				builtins(t_main *m, char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (ft_echo(m, m->arr, m->ehead));
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (ft_cd(m, (m->arr)[1]));
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (ft_pwd(m, m->ehead));
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (ft_export(m, m->arr, m->ehead));
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (ft_unset(m, m->arr, m->ehead));
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (ft_env(m, m->ehead));
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (ft_exit(m, m->arr));
	return (0);
}