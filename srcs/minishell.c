/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:11:18 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/29 12:09:03 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		prompt(int exit_status)
{
	ft_putstr("\e[0;32m\e[1mminish\e[0m");
	if (exit_status == 0)
		ft_putstr("\e[0;32m\e[1m $ \e[0m");
	else
		ft_putstr("\e[0;31m\e[1m $ \e[0m");
}

static void		init_cursor(t_main *m)
{
	m->p->lpos = 0;
	m->p->hnum = 0;
	m->p->lnum = 0;
	m->p->spos = 0;
	m->p->multi = 0;
}

static int		init_shell(t_main **m, char **env)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	if (!(*m = malloc(sizeof(t_main))))
		return (0);
	(*m)->arr = NULL;
	(*m)->env = env;
	(*m)->ehead = malloc(sizeof(t_list));
	(*m)->ehead = env_parser((*m)->ehead, env);
	(*m)->home = ft_strdup(get_env((*m)->ehead, "HOME"));
	(*m)->p = malloc(sizeof(t_cursor));
	(*m)->hist = init_history();
	(*m)->base_term = malloc(sizeof(struct termios));
	if (!((*m)->ehead) || !((*m)->home) || !((*m)->p) ||
		!((*m)->hist) || !((*m)->base_term))
			return (0);
	init_cursor(*m);
	(*m)->hist_path = ft_strjoin(get_env((*m)->ehead, "PWD"), "/.minish_history");
	(*m)->pathdirs = path_parser((*m)->ehead);
	(*m)->exit_status = 0;
	tcgetattr(STDIN_FILENO, (*m)->base_term);
	return (1);
}

void			print_lst_tokens(t_lexer *lexer)
{
	t_list	*toto;

	toto = lexer->tokens;
	printf("\n LEXER \n");
	while (toto)
	{
		t_token *t = toto->content;
		printf("%s     ---------- %u\n", t->data, t->type);
		toto = toto->next;
	}
	printf("nb=%d\n", lexer->nb_tokens);
}

int				main(int ac, char **av, char **env)
{
	char		*s;
	t_main		*m;
	t_lexer		*lexer;
	t_node		*exec_tree;

	(void)ac;
	(void)av;
	m = NULL;
	if (!(init_shell(&m, env)))
		malloc_error(m, NULL, NO_READING);
	while (1)
	{
		set_term_noncano();
		prompt(m->exit_status);
		s = line_read(m);
		if ((lexer = build_lexer(m, s)))
			if (parse(lexer, &exec_tree, s, m))
			{
				execute_command_line(m, exec_tree, 0);
				ast_delete_node(exec_tree);
			}
		printf("exit status = %d\n", m->exit_status);
	}
	return (0);
}
