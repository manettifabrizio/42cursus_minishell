/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:59 by viroques          #+#    #+#             */
/*   Updated: 2021/04/06 01:05:32 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_preorder(t_node *node)
{
	if (node == NULL)
		return ;
	printf("%s %i par%i\n", node->data, node->type, node->parenthese);
	print_preorder(node->left);
	print_preorder(node->right);
}

int				return_parse(t_list *tokens, t_node **exec_tree, \
	t_lexer *lexer, t_main *m)
{
	if (tokens != NULL || !exec_tree)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
		ft_putstr_fd(" near unexpected token: `", STDERR_FILENO);
		if (tokens != NULL)
			ft_putstr_fd(t_access_tok(tokens)->data, STDERR_FILENO);
		else if (!exec_tree)
			ft_putstr_fd(t_access_tok(lexer->tokens)->data, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		m->exit_status = 258;
		return (0);
	}
	return (1);
}

void			sort_parenthese(t_node *exec_tree)
{
	t_node *node;

	node = exec_tree;
	while (node)
	{
		if (node->left && node->left->parenthese)
		{
			if (node->right && node->right->left)
				node->right->left->parenthese = node->left->parenthese;
		}
		node = node->right;
	}
}

int				parse(t_lexer *lexer, t_node **exec_tree, char *s, t_main *m)
{
	t_list	*tokens;
	int		type;

	tokens = lexer->tokens;
	*exec_tree = build_line(&(tokens), m);
	sort_parenthese(*exec_tree);
	// print_preorder(*exec_tree);
	if (tokens != NULL && !tokens->next)
	{
		//no call multiligne after ;
		type = t_access_tok(tokens)->type;
		if (type == DPIPE || type == DAMPERSTAND || type == PIPE
			|| type == CLOSE_PAR)
		{
			if ((s = multilines(m, s, type)))
			{
				lexer = build_lexer(m, s);
				ast_delete_node(*exec_tree);
				return (parse(lexer, exec_tree, s, m));
			}
		}
	}
	return (return_parse(tokens, exec_tree, lexer, m));
}
