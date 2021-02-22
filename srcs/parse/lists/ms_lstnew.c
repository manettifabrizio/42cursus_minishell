/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:35:00 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/15 18:12:19 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_e()
{
	t_env	*element;

	if (!(element = malloc(sizeof(*element))))
		return (NULL);
	element->name = NULL;
	element->value = NULL;
	element->next = NULL; 
	return (element);
}