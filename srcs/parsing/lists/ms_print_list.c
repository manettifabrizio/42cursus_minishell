/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:12:30 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/02 17:04:07 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_print_list(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		else
			printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}