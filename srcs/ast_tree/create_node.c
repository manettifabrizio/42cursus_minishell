/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:16:22 by viroques          #+#    #+#             */
/*   Updated: 2021/03/24 15:17:12 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node			*create_node(int type, char *data)
{
	t_node	*new;

	if (!(new = malloc(sizeof(t_node))))
		return (NULL);
	ast_set_type(new, type);
	ast_set_data(new, data);
	return (new);
}
