/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:34:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/11 20:08:34 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		backspace(char *s, t_cursor *p)
{
	t_uint	len;
	
	len = ft_strlen(s);
	if (len == 0)
		return (1);
	if (len > 0 && s[len - 1] != '\n' && p->spos == 0)
	{
		ft_putstr("\b \b");
		s[len - 1] = '\0';
	}
	else if (s[len - 1] == '\n' && count_lines(s) > 1 && p->lnum > 0)
	{
		ft_putstr(CURSOR_UP);
		s[len - 1] = '\0';
		(p->lnum)--;
		p->lpos = ft_strlen(p->arr[p->lnum]);
		if (p->lnum == 0)
			p->lpos += 9;
		end(p->arr[p->lnum], p);
	}
	return ((p->spos == 0) ? 1 : 0);
}

int		delete(char *s, char *buf, t_cursor *p)
{
	read(STDOUT_FILENO, buf, 1);
	if (buf[0] == '~')
	{
		if (ft_strlen(s) == 0 || p->lpos == 0)
			return (1);
		arrow_right(s, p);
		if (p->lpos == 0)
			return (backspace(s, p));
		else
			buf[0] = BACKSPACE;
	}
	return (0);
}