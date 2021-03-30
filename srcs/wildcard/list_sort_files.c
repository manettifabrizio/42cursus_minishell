/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 00:39:37 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/25 10:19:07 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		copy_list(t_list **head, t_list **lhead)
{
	t_list	*l;

	*lhead = NULL;
	l = *head;
	// print_list_files(*head);
	// printf("================\n");
	while (l)
	{
		add_elem_to_list(lhead, t_access_files(l)->name);
		// print_list_files(*lhead);
		// printf("================\n");
		l = l->next;
	}
}

t_list			*list_sort_files(t_list **head)
{
	t_list	*l;
	t_list	*lhead;
	char	**s;
	char	**snext;

	copy_list(head, &lhead);
	if (!head || !lhead)
		return (NULL);
	l = lhead;
	while (l->next)
	{
		s = &(t_access_files(l)->name);
		snext = &(t_access_files(l->next)->name);
		if (ft_strcmp(*s, *snext) > 0)
		{
			ft_swap_s(s, snext);
			l = lhead;
		}
		else
			l = l->next;
	}
	// free_list()
	return (lhead);
}