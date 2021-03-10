/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:11:18 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 14:25:21 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(int exit_status)
{
	if (signaln == SIGINT || signaln == SIGQUIT)
		ft_putchar('\n');
	ft_putstr("\e[0;32m\e[1mminish\e[0m");
	if (exit_status == 0)
		ft_putstr("\e[0;32m\e[1m $ \e[0m");
	else
		ft_putstr("\e[0;31m\e[1m $ \e[0m");
}

// void	line_execute(t_main *m, char **env)
// {
// 	if ((m->arr)[1])
// 		if (ft_strcmp((m->arr)[1], "<<") == 0)
// 			{
// 				heredoc(m, (m->arr)[2]);
// 				redirect(); // <
// 			}
// }

static int		init_shell(t_main *m, char **env)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	m->env = env;
	m->ehead = malloc(sizeof(t_list));
	if (!(m->ehead = env_parser(m->ehead, env)))
		return (0);
	if (!(m->home = ft_strdup(get_env(m->ehead, "HOME"))))
		return (0);
	if (!(m->pos = malloc(sizeof(t_cursor))))
		return (0);
	m->pos->x = 0;
	m->pos->y = 0;
	m->hist_path = ft_strjoin(get_env(m->ehead, "PWD"), "/.minish_history");
	m->pathdirs = path_parser(m->ehead);
	if (!(m->base_term = malloc(sizeof(struct termios))))
		return (0);
	m->exit_status = 0;
	tcgetattr(STDIN_FILENO, m->base_term);
	return (1);
}

void	print_lst_tokens(t_lexer *lexer)
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

int		main(int ac, char **av, char **env)
{
	char		*s;
	t_main		*m;
	t_lexer		*lexer;
    t_node		*exec_tree;

	ac = 1; av = NULL;
	if (!(m = malloc(sizeof(t_main))))
		malloc_error(m, NULL, NO_READING);
	if (!(init_shell(m, env)))
		malloc_error(m, NULL, NO_READING);
	if (!(m->hist = init_history()))
		malloc_error(m, NULL, NO_READING);
	while (1)
	{
		config_term(1, m->base_term);
		
		// READ
		prompt(m->exit_status);
		signaln = 0;
		s = line_read(m);
		
		// LEXE && PARSE
		lexer = build_lexer(m, s);
		// print_lst_tokens(lexer);
		if (m->arr)
			free(m->arr);
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
		// printf("exit status = %d\n", m->exit_status);
	}
	make_history(m->hist_path, m->hist);
	config_term(0, m->base_term);
	return (0);
}