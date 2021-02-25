/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:35:38 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/23 13:35:40 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arrow_up()
{
	return (1);
}

int		arrow_down()
{
	return (1);
}

int		arrow_right(t_cursor *pos)
{
	if (pos->x > 0)
	{
		(pos->x)--;
		ft_putstr(CURSOR_RIGHT);
	}
	return (1);
}

int		arrow_left(char *s, t_cursor *pos)
{
	if (pos->x < ft_strlen(s))
	{
		(pos->x)++;
		ft_putstr(CURSOR_LEFT);
	}
	return (1);
}