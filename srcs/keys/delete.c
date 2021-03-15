/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:34:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/16 00:39:03 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		backspace(char *s, t_cursor *p)
{
	t_uint	len;
	
	len = ft_strlen(s);
	if (len == 0)
		return (1);
	if (len > 0 && s[len - 1] != '\n' && p->lpos == 0 && p->spos == 0)
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
			p->lpos += (p->multi == 0) ? 9 : 2; // prompt or multi prompt
		end(p->arr[p->lnum], p);
	}
	return ((p->spos == 0) ? 1 : 0);
}

int		delete(char *s, char *buf, t_cursor *p)
{
	t_uint pos;

	read(STDOUT_FILENO, buf, 1);
	if (buf[0] == '~')
	{
		pos = (count_lines(s) == 1) ? p->lpos : p->spos;
		if (ft_strlen(s) == 0 || pos == 0)
			return (1);
		arrow_right(s, p);
		// pos = (count_lines(s) == 1) ? p->lpos : p->spos;
		// printf("lpos = %u spos = %u\n", p->lpos, p->spos);
		if (p->spos == 0)
			return (backspace(s, p));
		else
			buf[0] = BACKSPACE;
	}
	return (0);
}