/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:23:19 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/02 18:30:36 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		copy_list(t_env *head, t_env **lhead)
{
	t_env	*l;
	t_env	*l1;

	l = head;
	while (l)
	{
		l1 = ft_lstnew_e();
		if (ft_strcmp(l->name, head->name) == 0)
			*lhead = l1;
		l1->name = l->name;
		l1->value = l->value;
		ft_lstadd_back_e(lhead, l1);
		l = l->next;
		l1 = l1->next;
	}
}

t_env	*ms_list_sort(t_env *head)
{
	t_env	*l;
	char	*tmp;
	t_env	*lhead;

	copy_list(head, &lhead);
	l = lhead;
	while (l->next)
		if (ft_strcmp(l->name, (l->next)->name) > 0)
		{
			// ms_print_list(l);
			// printf("\n\n");
			tmp = l->name;
			l->name = (l->next)->name;
			(l->next)->name = tmp;
			tmp = l->value;
			l->value = (l->next)->value;
			(l->next)->value = tmp;
			l = lhead;
		}
		else
			l = l->next;
	return (lhead);
}