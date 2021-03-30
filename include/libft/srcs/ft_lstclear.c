/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:10:09 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/29 14:53:34 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*actual;

	if (!lst || !*lst)
		return ;
	actual = *lst;
	while (actual)
	{
		tmp = actual;
		del(actual->content);
		free(tmp);
		actual = actual->next;
	}
	*lst = NULL;
}
