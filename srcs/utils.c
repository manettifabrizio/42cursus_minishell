/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:15:14 by viroques          #+#    #+#             */
/*   Updated: 2021/03/08 18:23:56 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*create_env_elem(char **a)
{
	t_env	*l;
	t_list	*tmp;

	if (!(l = malloc(sizeof(t_env))))
		return (0);
	l->name = a[0];
	if (a[1])
		l->value = a[1];
	if (!(tmp = ft_lstnew(l)))
		return (0);
	return (tmp);
}