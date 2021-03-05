/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/05 14:32:58 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	if (signaln == SIGINT || signaln == SIGQUIT)
		ft_putchar('\n');
	ft_putstr("\e[0;32m\e[1mminish $ \e[0m");
}

// void	redirect()
// {}

// void	line_execute(t_main *m, char **env)
// {
// 	if ((m->arr)[1])
// 		if (ft_strcmp((m->arr)[1], "<<") == 0)
// 			{
// 				heredoc(m, (m->arr)[2]);
// 				redirect(); // <
// 			}
// 	if (!(builtins(m)))
// 	{
// 		if (!(search_path(m, env)))
// 		{
// 			error(1, "command not found");
// 			m->exit_status = 127;
// 		}
// 	}
// }

static void		init_shell(t_main *m, char **env)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	m->env = env;
	m->ehead = env_parser(m->ehead, env);
	if (!(m->pos = malloc(sizeof(t_cursor))))
		return ; //error
	m->pos->x = 0;
	m->pos->y = 0;
	m->hist_path = ft_strjoin(get_env(m->ehead, "PWD"), "/.minish_history");
	m->pathdirs = path_parser(m->ehead);
	if (!(m->base_term = malloc(sizeof(struct termios))))
		return ; //error
	m->exit_status = 0;
	tcgetattr(STDIN_FILENO, m->base_term);
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

void	free_lexer(t_list *lst_tokens)
{
    t_list *lst;
    t_list *tmp;
    t_token *tok;

    lst = lst_tokens;
    while (lst)
    {
        tok = lst->content;
        free(tok->data);
        free(tok);
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
}

int		main(int ac, char **av, char **env)
{
	char		*s;
	t_main		*m;
	t_lexer		*lexer;
    t_node		*exec_tree;

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
		if (!(lexer = malloc(sizeof(t_lexer))))
        	return (-1);
		lexer->tokens = NULL;
		lexer->nb_tokens = 0;
		
		m->arr = ft_split(s, ' ');
		if (build_lexer(m->arr, lexer) == -1)
            free_lexer(lexer->tokens);
		if (lexer->nb_tokens == 0 || parse(lexer, &exec_tree) == -1)
			error(NO_ERRNO, "parse error");
		free_lexer(lexer->tokens);
		
		// EXECUTE
		execute_ast_tree(m, exec_tree);
        ast_delete_node(exec_tree);

		printf("exit status = %d\n", m->exit_status);
		// ms_print_list(m->ehead);
	}
	make_history(m->hist_path, m->hist);
	config_term(0, m->base_term);
	return (0);
}