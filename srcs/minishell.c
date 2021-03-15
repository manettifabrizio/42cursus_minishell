/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:11:18 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/16 00:58:41 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prompt(int exit_status)
{
	ft_putstr("\e[0;32m\e[1mminish\e[0m");
	if (exit_status == 0)
		ft_putstr("\e[0;32m\e[1m $ \e[0m");
	else
		ft_putstr("\e[0;31m\e[1m $ \e[0m");
}

static int init_shell(t_main *m, char **env)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	m->arr = NULL;
	m->env = env;
	m->ehead = malloc(sizeof(t_list));
	if (!(m->ehead = env_parser(m->ehead, env)))
		return (0);
	if (!(m->home = ft_strdup(get_env(m->ehead, "HOME"))))
		return (0);
	if (!(m->p = malloc(sizeof(t_cursor))))
		return (0);
	m->p->lpos = 0;
	m->p->hnum = 0;
	m->p->lnum = 0;
	m->p->spos = 0;
	m->p->multi = 0;
	m->hist_path = ft_strjoin(get_env(m->ehead, "PWD"), "/.minish_history");
	m->pathdirs = path_parser(m->ehead);
	if (!(m->base_term = malloc(sizeof(struct termios))))
		return (0);
	m->exit_status = 0;
	tcgetattr(STDIN_FILENO, m->base_term);
	return (1);
}

void print_lst_tokens(t_lexer *lexer)
{
	t_list *toto;

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

int main(int ac, char **av, char **env)
{
	char *s;
	t_main *m;
	t_lexer *lexer;
	t_node *exec_tree;

	ac = 1;
	av = NULL;
	if (!(m = malloc(sizeof(t_main))))
		malloc_error(m, NULL, NO_READING);
	if (!(init_shell(m, env)))
		malloc_error(m, NULL, NO_READING);
	if (!(m->hist = init_history()))
		malloc_error(m, NULL, NO_READING);
	while (1)
	{
		set_term_noncano();

		// READ
		prompt(m->exit_status);
		s = line_read(m);
		// LEXE && PARSE
		if ((lexer = build_lexer(m, s)))
		{
			if (m->arr)
				ft_free_array(m->arr);
			if (lexer->nb_tokens > 0)
			{
				if (parse(lexer, &exec_tree))
				{
					//execute
					execute_ast_tree(m, exec_tree);
					ast_delete_node(exec_tree);
				}
			}
			free_lexer(lexer);
		}
		printf("exit status = %d\n", m->exit_status);
	}
	make_history(m->hist_path, m->hist);
	set_term_cano(m->base_term);
	return (0);
}