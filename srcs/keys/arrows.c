/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:35:38 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/26 13:06:15 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arrow_up(char **s, char **h, t_cursor *pos)
{
	int		i;

	i = -1;
	while (h[++i]);
	if (pos->y == (t_uint)i)
		return (1);
	if (pos->y < (t_uint)(i - 1))
		(pos->y)++;
	home(*s, pos);
	ft_putstr(CLEAR_LINE);
	ft_putstr(h[pos->y]);
	pos->x = 0;
	free(*s);
	(*s) = ft_strdup(h[pos->y]);
	return (1);
}

int		arrow_down(char **s, char **h, t_cursor *pos)
{
	int		i;

	i = -1;
	while (h[++i]);
	home(*s, pos);
	if (pos->y > 0)
		(pos->y)--;
	ft_putstr(CLEAR_LINE);
	ft_putstr(h[pos->y]);
	pos->x = 0;
	free(*s);
	(*s) = ft_strdup(h[pos->y]);
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