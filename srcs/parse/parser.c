/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:59 by viroques          #+#    #+#             */
/*   Updated: 2021/04/01 17:31:09 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_preorder(t_node *node)
{
	if (node == NULL)
		return ;
	printf("%s %i\n", node->data, node->type);
	print_preorder(node->left);
	print_preorder(node->right);
}

int				return_parse(t_list *tokens, t_node **exec_tree, \
	t_lexer *lexer, t_main *m)
{
	if (tokens != NULL)
	{
		printf("minish: %s near unexpected token: `%s'\n", SYNTAX_ERROR,
			t_access_tok(tokens)->data);
		m->exit_status = 258;
		return (0);
	}
	if (!*exec_tree)
	{
		printf("minish: %s near unexpected token: `%s'\n", SYNTAX_ERROR,
			t_access_tok(lexer->tokens)->data);
		m->exit_status = 258;
		return (0);
	}
	return (1);
}

int				call_multilines(t_lexer *lexer, t_list *tokens)
{
	t_list *check;

	check = lexer->tokens;
	if (tokens != NULL && !tokens->next && tokens != lexer->tokens)
	{
		while (check)
		{
			if (check->next && check->next == tokens)
			{
				if (t_access_tok(check)->type != SEMICOLON)
					return (1);
			}
			check = check->next;
		}
	}
	return (0);
}

int				parse(t_lexer *lexer, t_node **exec_tree, char *s, t_main *m)
{
	t_list	*tokens;
	int		par;
	int		type;

	par = 0;
	tokens = lexer->tokens;
	*exec_tree = build_line(&(tokens), par);
	if (call_multilines(lexer, tokens))
	{
		type = t_access_tok(tokens)->type;
		if (type == DPIPE || type == DAMPERSTAND || type == PIPE
			|| type == CLOSE_PAR)
		{
			s = multilines(m, s, type);
			lexer = build_lexer(m, s);
			ast_delete_node(*exec_tree);
			return (parse(lexer, exec_tree, s, m));
		}
	}
	return (return_parse(tokens, exec_tree, lexer, m));
}
