/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:34:34 by fmanetti          #+#    #+#             */
/*   Updated: 2021/01/28 14:34:35 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_e(t_env **alst, t_env *new)
{
	if (!new)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		ft_lstlast_e(*alst)->next = new;
		new->next = NULL;
	}
}