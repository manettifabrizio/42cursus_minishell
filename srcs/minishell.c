/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/26 12:38:53 by fmanetti         ###   ########.fr       */
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
	if (!(m->base_term = malloc(sizeof(struct termios))))
		return ; //error
	if (!(m->pos = malloc(sizeof(t_cursor))))
		return ; //error
	tcgetattr(STDIN_FILENO, m->base_term);
	m->pos->x = 0;
	m->pos->y = 0;
	if (!(m->hist = malloc(1 * sizeof(char*))))
		return ; //error
	m->hist[0] = NULL;
}

int		main(int ac, char **av, char **env)
{
	char		*s;
	t_main		*m;

	ac = 1; av = NULL;
	if (!(m = malloc(sizeof(t_main))))
		return (0); //error
	init_shell(m);
	line_parse(m, env);
	while (1)
	{
		// printf("pos = %d\n", m->pos->x);
		set_term(1, m->base_term);
		prompt();
		signaln = 0;
		s = line_read(m);
		// ft_print_array(m->hist);
		m->arr = ft_split(s, ' ');
		// ft_print_array(m->arr);
		if ((m->arr)[0])
			line_execute(m, env);
		// ms_print_list(m->ehead);
	}
	set_term(0, m->base_term);
	return (0);
}