/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:53:25 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/23 14:13:17 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		home(char *s, t_cursor *pos)
{
	int		i;

	i = ft_strlen(s) - pos->x;
	while (i--)
		arrow_left(s, pos);
	return (1);
}

int		end(t_cursor *pos)
{
	int		i;

	i = pos->x;
	while (i--)
		arrow_right(pos);
	return (1);
}