/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:56:35 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/02 20:05:24 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_echo(char **a)
{
	int x;

	x = 1;
	if (!(a[1]))
		printf("\n");
	else
		if (ft_strcmp(a[1], "-n") == 0)
		{
			if (a[2])
				while (a[++x])
				{
					ft_putstr(a[x]);
					if (a[x + 1])
						ft_putchar(' ');
				}
		}
		else
		{
			while (a[x])
			{
				ft_putstr(a[x++]);
				if (a[x])
					ft_putchar(' ');
			}
			printf ("\n");
		}
	return (1);
}

static int		ft_cd(char **a)
{
	if (!(a[1]))
		chdir("/");
	else
	{
		if (chdir(a[1]) != 0)
		{
			printf("%s\n", strerror(errno));
			return (0);
		}
	}
	return (1);
}

static int		ft_pwd()
{
	char *str;
	char buf[1024];
	
	if (!(str = getcwd(buf, 1024)))
		return (0); //error
	printf ("%s\n", str);
	return (1);
}

static int		ft_env(t_env *head)
{
	t_env	*l;

	l = head;
	while (l != NULL)
	{
		if (l->value)
			printf("%s=%s\n", l->name, l->value);
		l = l->next;
	}
	return (1);
}

static int		ft_exit()
{
	exit(0);
	return (1);
}

int				builtins(t_main *m)
{
	if (ft_strcmp((m->arr)[0], "echo") == 0)
		return (ft_echo(m->arr));
	else if (ft_strcmp((m->arr)[0], "cd") == 0) // absolut path or relative
		return (ft_cd(m->arr));
	else if (ft_strcmp((m->arr)[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp((m->arr)[0], "export") == 0)
		return (ft_export(m->arr, m->ehead));
	else if (ft_strcmp((m->arr)[0], "unset") == 0)
		return (ft_unset(m->arr, m->ehead));
	else if (ft_strcmp((m->arr)[0], "env") == 0)
		return (ft_env(m->ehead));
	else if (ft_strcmp((m->arr)[0], "exit") == 0)
		return (ft_exit());
	return (0);
}