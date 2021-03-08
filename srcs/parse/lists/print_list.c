/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:12:30 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 14:32:09 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (t_access_env(tmp)->value)
			printf("%s=%s\n", t_access_env(tmp)->name, t_access_env(tmp)->value);
		else
			printf("%s\n", t_access_env(tmp)->name);
		tmp = tmp->next;
	}
}