/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:12:30 by fmanetti          #+#    #+#             */
/*   Updated: 2021/01/28 18:06:25 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_list(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("* %s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}