/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:59 by viroques          #+#    #+#             */
/*   Updated: 2021/03/08 20:55:53 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check(t_token_type tok_type, char** bufferptr, t_list **token)
{
	if (*token == NULL)
		return 0;
    if (t_access_tok(*token)->type == tok_type)
    {
		if (bufferptr != NULL) {
			if (!(*bufferptr = ft_strdup(t_access_tok(*token)->data)))
                return (-1);
		}
		*token = (*token)->next;
        return (1);
    }
    *token = (*token)->next;
    return (0);
}

void        print_preorder(t_node *node)
{
    if (node == NULL)
        return;
    printf("%s %i\n", node->data, node ->type);
    print_preorder(node->left);
    print_preorder(node->right);
}

int       parse(t_lexer *lexer, t_node **exec_tree)
{
    t_list *tokens;

    tokens = lexer->tokens;
    *exec_tree = build_line(&(tokens));
     if (tokens != NULL)
     {
         printf("minish: Syntax error near: %s\n", t_access_tok(tokens)->data);
         return (0);
     }
    // printf("PARSING\n");
    // print_preorder(*exec_tree);
    return (1);
} 