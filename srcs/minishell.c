/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/17 18:00:56 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	if (signaln == SIGINT || signaln == SIGQUIT)
		ft_putchar('\n');
	ft_putstr("\e[0;32m\e[1mminish $ \e[0m");
}

void	line_execute(t_main *m, char **env)
{
	// printf("m3 = %p\n", m);
	if (!(builtins(m)))
	{
		// printf("Error: builtin not found");
		if (!(search_path(*m, env)))
			printf("Error: command not found\n"); //ERROR: command not found
	}
	// ms_print_list(m->ehead);
}

static void		init_shell(t_main *m)
{
	signaln = 0;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	// if (!(m = malloc(sizeof(t_main))))
	// 	return ; //error
	if (!(m->base_term = malloc(sizeof(struct termios))))
		return ;
	// printf("base_term0 = %p\n", m->base_term);
	// printf("m1 = %p\n", m);
	tcgetattr(STDIN_FILENO, m->base_term);
	// printf("base_term1 = %p\n", m->base_term);
	// set_term(1, m->base_term);
	// printf("terminos off\n");
}

int		main(int ac, char **av, char **env)
{
	char		*str;
	t_main		m;
	int x;

	ac = 1; av = NULL;
	// ft_print_array(env);
	init_shell(&m);
	line_parse(&m, env);
	while (1)
	{
		set_term(1, m.base_term);
		prompt();
		signaln = 0;
		// printf ("2\n");
		m.arr = line_read(m.base_term);
		// // ft_print_array(m.arr);
		// // if (strcmp("echo", m.arr[0]))
		// // 		m.arr[1] = av[1]
		// // printf("str = %s", str);
		if ((m.arr)[0])
			line_execute(&m, env);
		// ms_print_list(m.ehead);
	}
	set_term(0, m.base_term);
	return (0);
}