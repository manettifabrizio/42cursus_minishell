/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:14:42 by viroques          #+#    #+#             */
/*   Updated: 2021/04/02 16:35:34 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check(t_token_type tok_type, char **bufferptr, t_list **token)
{
	if (*token == NULL)
		return (0);
	if (t_access_tok(*token)->type == tok_type)
	{
		if (bufferptr != NULL)
			if (!(*bufferptr = ft_strdup(t_access_tok(*token)->data)))
				return (-1);
		*token = (*token)->next;
		return (1);
	}
	*token = (*token)->next;
	return (0);
}

t_node			*return_err_check_par(t_list **token)
{
	t_list *multi;
	t_token *tok;

	if (!(tok = malloc(sizeof(t_token))))
		return (NULL);
	tok->type = CLOSE_PAR;
	tok->data = NULL;
	if (!(multi = ft_lstnew(tok)))
		return (NULL);
	ft_lstadd_back(token, multi);
	return (NULL);
}

t_node			*check_closing_par(int par, t_list **token, t_node *node)
{
	t_node *line;
	t_node *logic;

	if (par)
	{
		if (!check_par(CLOSE_PAR, NULL, token))
			return (return_err_check_par(token));
		if (check_par(DPIPE, NULL, token))
		{
			logic = create_node(NODE_LOGIC_PIPE, ft_strdup("close par"));
			line = build_line(token, 0);
			ast_attach_branch(logic, node->right, line);
			ast_attach_right(node, logic);
		}
		else if (check_par(DAMPERSTAND, NULL, token))
		{
			logic = create_node(NODE_LOGIC_AMPERSTAND, ft_strdup("close par"));
			line = build_line(token, 0);
			ast_attach_branch(logic, node->right, line);
			ast_attach_right(node, logic);
		}
	}
	return (node);
}

int				check_par(t_token_type tok_type,
							char **bufferptr, t_list **token)
{
	if (token == NULL || *token == NULL)
		return (0);
	if (t_access_tok(*token)->type == tok_type)
	{
		if (bufferptr != NULL)
			if (!(*bufferptr = ft_strdup(t_access_tok(*token)->data)))
				return (-1);
		*token = (*token)->next;
		return (1);
	}
	return (0);
}
