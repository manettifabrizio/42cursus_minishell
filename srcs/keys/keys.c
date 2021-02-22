/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:20:49 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/22 22:45:55 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_strdelone(char *s, unsigned int n)
// {
// 	int		x;
// 	int		len;
// 	char	*tmp;

// 	len = ft_strlen(s);
// 	tmp = ft_substr(s, n, len - n);
	

// }

int		backspace(char *s, t_cursor *pos)
{
	int x;
	
	x = ft_strlen(s);
	if (x > 0 && pos->x == 0)
	{
		s[x - 1] = '\0';
		ft_putstr("\b \b");
		return (1);
	}
	return (0);
}

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