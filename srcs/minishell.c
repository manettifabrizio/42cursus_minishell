/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/27 20:41:34 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	if (signaln == SIGINT || signaln == SIGQUIT)
		ft_putchar('\n');
	ft_putstr("\e[0;32m\e[1mminish $ \e[0m");
}

void	redirect()
{}

void	line_execute(t_main *m, char **env)
{
	if ((m->arr)[1])
		if (ft_strcmp((m->arr)[1], "<<") == 0)
			{
				heredoc(m, (m->arr)[2]);
				redirect(); // <
			}
	// ^\ in cat stopped working rimane in non-canonic
	if (!(builtins(m)))
	{
		if (!(search_path(*m, env)))
			printf("Error: command not found\n"); //ERROR: command not found
	}
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
}

int		main(int ac, char **av, char **env)
{
	char		*s;
	t_main		*m;

	ac = 1; av = NULL;
	if (!(m = malloc(sizeof(t_main))))
		return (0); //error
	init_shell(m);
	shell_parse(m, env);
	m->hist = init_history();
	while (1)
	{
		set_term(1, m->base_term);
		
		// READ
		prompt();
		s = line_read(m);

		// LEXE && PARSE
		m->arr = ft_split(s, ' ');

		// EXECUTE
		if ((m->arr)[0])
			line_execute(m, env);
		// ms_print_list(m->ehead);
	}
	make_history(m->hist);
	set_term(0, m->base_term);
	return (0);
}