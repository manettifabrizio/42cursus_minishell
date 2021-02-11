/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/11 14:21:24 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	write(1, "\e[0;36m\e[1mminish # \e[0m", 24);
}

void	line_execute(t_main *m, char **env)
{
	if (!(builtins(m)))
	{
		// printf("Error: builtin not found");
		if (!(search_path(*m, env)))
			printf("Error: command not found\n"); //ERROR: command not found
	}
	// ms_print_list(m->ehead);
}

static	void	ciao(int x)
{
	if (x == 3)
		printf("\n");
	if (x == 2)
		ft_putstr("\b\b  \b\b");
}

static void		init_shell()
{
	signal(SIGINT, &ciao);
	signal(SIGQUIT, &ciao);
}

int		main(int ac, char **av, char **env)
{
	char		*str;
	t_main		m;
	int x;

	ac = 1; av = NULL;
	// ft_print_array(env);
	init_shell();
	line_parse(&m, env);
	while (1)
	{
		prompt();
		m.arr = line_read();
		// ft_print_array(m.arr);
		// if (strcmp("echo", m.arr[0]))
		// 		m.arr[1] = av[1]
		// printf("str = %s", str);
		if ((m.arr)[0])
			line_execute(&m, env);
		// ms_print_list(m.ehead);
	}
	return (0);
}