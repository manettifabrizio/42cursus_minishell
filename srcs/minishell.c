/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/04 18:57:32 by fmanetti         ###   ########.fr       */
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
	if (!(builtins(m)))
	{
		if (!(search_path(m, env)))
		{
			error(1, "command not found");
			m->exit_status = 127;
		}
	}
}

static void		init_shell(t_main *m, char **env)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	m->ehead = env_parser(m->ehead, env);
	if (!(m->pos = malloc(sizeof(t_cursor))))
		return ; //error
	m->pos->x = 0;
	m->pos->y = 0;
	m->hist_path = ft_strjoin(get_env(m->ehead, "PWD"), "/.minish_history");
	m->path = path_parser(m->ehead);
	if (!(m->base_term = malloc(sizeof(struct termios))))
		return ; //error
	m->exit_status = 0;
	tcgetattr(STDIN_FILENO, m->base_term);
}

int		main(int ac, char **av, char **env)
{
	char		*s;
	t_main		*m;

	ac = 1; av = NULL;
	if (!(m = malloc(sizeof(t_main))))
		return (0); //error
	init_shell(m, env);
	// printf("init_shell\n");
	m->hist = init_history();
	while (1)
	{
		config_term(1, m->base_term);
		// READ
		prompt();
		signaln = 0;
		s = line_read(m);
		// LEXE && PARSE
		m->arr = ft_split(s, ' ');

		// EXECUTE
		if ((m->arr)[0])
			line_execute(m, env);
		printf("exit status = %d\n", m->exit_status);
		// ms_print_list(m->ehead);
	}
	make_history(m->hist_path, m->hist);
	config_term(0, m->base_term);
	return (0);
}