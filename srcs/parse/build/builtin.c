/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:30:47 by viroques          #+#    #+#             */
/*   Updated: 2021/03/29 14:54:51 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node		*build_builtin_1(t_list **token)
{
	t_node	*result;
	t_node	*args;
	char	*pathname;

	if (!check(WORD, &pathname, token))
		return (NULL);
	args = build_args(token);
	if (!(result = create_node(NODE_BUILTIN, pathname)))
		return (NULL);
	ast_attach_branch(result, args, NULL);
	return (result);
}

t_node				*build_builtin(t_list **token)
{
	t_list	*save;
	t_node	*builtin;

	save = *token;
	if (!(builtin = build_builtin_1(token)))
		*token = save;
	return (builtin);
}
