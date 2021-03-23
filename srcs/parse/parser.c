/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:59 by viroques          #+#    #+#             */
/*   Updated: 2021/03/23 16:41:18 by viroques         ###   ########.fr       */
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

t_node      *create_node(int type, char *data)
{
    t_node      *new;

    if (!(new = malloc(sizeof(t_node))))
        return (NULL);
    ast_set_type(new, type);
    if (data)
        ast_set_data(new, ft_strdup(data));
    else
        ast_set_data(new, NULL);
    return (new);
}

t_node      *check_closing_par(int par, t_list **token, t_node *node)
{
    t_node *line;
    t_node *logic;

    if (par)
    {
        if (!check_par(CLOSE_PAR, NULL, token))
        {
            ast_delete_node(node);
            printf("minish: Missing closing parenthese\n");
            return (NULL);
        }
        if (check_par(DPIPE, NULL, token))
        {
            logic = create_node(NODE_LOGIC_PIPE, "close par");
            line = build_line(token, 0);
            ast_attach_branch(logic, node->right, line);
            ast_attach_right(node, logic);
        }
        else if (check_par(DAMPERSTAND, NULL, token))
        {
            logic = create_node(NODE_LOGIC_AMPERSTAND, "close par");
            line = build_line(token, 0);
            ast_attach_branch(logic, node->right, line);
            ast_attach_right(node, logic);
        }
    }
    return (node);
}

int     check_par(t_token_type tok_type, char** bufferptr, t_list **token)
{
	if (token == NULL || *token == NULL)
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

int       parse(t_lexer *lexer, t_node **exec_tree, char *s, t_main *m)
{
    t_list  *tokens;
    int     par;
    int     type;
    
    par = 0;
    tokens = lexer->tokens;
    *exec_tree = build_line(&(tokens), par);
    if (tokens != NULL && !tokens->next)
    {
        type = t_access_tok(tokens)->type;
        s = multilines(m, s, type);
        lexer = build_lexer(m, s);
        ast_delete_node(*exec_tree);
        return (parse(lexer, exec_tree, s, m));
    }
    if (tokens != NULL)
    {
         printf("minish: Syntax error near unexpected token: %s\n", t_access_tok(tokens)->data);
         return (0);
     }
     if (!*exec_tree)
     {
        printf("minish: Syntax error near unexpected token: %s\n", t_access_tok(lexer->tokens)->data);
         return (0);
     }
    //  printf("PARSER -----------\n");
    //  print_preorder(*exec_tree);
    return (1);
} 