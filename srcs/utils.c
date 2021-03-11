/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:15:14 by viroques          #+#    #+#             */
/*   Updated: 2021/03/11 18:01:25 by fmanetti         ###   ########.fr       */
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
	else
		l->value = NULL;
	if (!(tmp = ft_lstnew(l)))
		return (0);
	return (tmp);
}

t_uint		count_lines(char *s)
{
	int		i;
	t_uint	nln;

	i = -1;
	nln = 1;
	while (s[++i])
		if (s[i] == '\n')
			nln++;
	return (nln);
}