/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:34:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/25 19:29:10 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		backspace(char *s, t_cursor pos)
{
	int x;
	
	x = ft_strlen(s);
	if (x == 0)
		return (1);
	if (x > 0 && pos.x == 0)
	{
		s[x - 1] = '\0';
		ft_putstr("\b \b");
		return (1);
	}
	return (0);
}

int		delete(char *s, char *buf, t_cursor *pos)
{
	read(STDOUT_FILENO, buf, 1);
	// printf("\nbuf = %d pos.x = %d s = |%s|\n", buf[0], pos->x, s);
	if (buf[0] == '~')
	{
		// printf("strlen = %lu\n", ft_strlen(s));
		if (ft_strlen(s) == 0 || pos->x == 0)
			return (1);
		if (pos->x != 0)
		{
			arrow_right(pos);
			if (pos->x == 0)
				return (backspace(s, *pos));
			else
				buf[0] = BACKSPACE;
		}
	}
	return (0);
}