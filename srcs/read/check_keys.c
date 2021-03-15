/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:21:23 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/15 21:41:47 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		word_move(char *s, t_cursor *p)
{
	char	buf[3];
	
	read(STDOUT_FILENO, buf, 2);
	buf[2] = '\0';
	if (ft_strcmp(buf, ";5") == 0)
	{
		read(STDOUT_FILENO, buf, 1);
		buf[1] = '\0';
		if (buf[0] == ARR_RIGHT)
			return (word_right(s, p));
		if (buf[0] == ARR_LEFT)
			return (word_left(s, p));
	}
	return (0);
}

int		home_end(char *s, char c, t_cursor *p)
{
	if (c == HOME)
		return (home(s, p));
	if (c == END)
		return (end(s, p));
	return (0);
}

static int		control(t_main *m, char *s, char *buf)
{
	if (buf[0] == CTRL_C)
		return (control_c(m, s));
	if (buf[0] == CTRL_D && s[0] == '\0')
	{
		if (ft_strlen(buf) == 2)
		{
			m->exit_status = 0;
			return (1);
		}
		else
			control_d(m);
	}
	return (0);
}

int		arrows(t_main *m, char **s, char c)
{
	if (c == ARR_UP)
		return (arrow_up(s, m->hist, m->p));
	if (c == ARR_DOWN)
		return (arrow_down(s, m->hist, m->p));
	if (c == ARR_RIGHT)
		return (arrow_right(*s, m->p));
	if (c == ARR_LEFT)
		return (arrow_left(*s, m->p));
	return (0);
}

int		check_key(t_main *m, char **s, char *buf)
{
	m->p->arr = split_keep(*s, '\n');
	if (buf[0] == CTRL_C || buf[0] == CTRL_D)
		return (control(m, *s, buf));
	if (buf[0] == BACKSPACE)
		return (backspace(*s, m->p));
	if (buf[0] == ESCAPE)
	{
		read(STDOUT_FILENO, buf, 1);
		if (buf[0] == '[')
		{
			read(STDOUT_FILENO, buf, 1);
			if (buf[0] == ARR_UP || buf[0] == ARR_DOWN ||
				buf[0] == ARR_RIGHT || buf[0] == ARR_LEFT)
				return (arrows(m, s, buf[0]));
			if (buf[0] == DELETE)
				return (delete(*s, buf, m->p));
			if (buf[0] == HOME || buf[0] == END)
				return (home_end(*s, buf[0], m->p));
			if (buf[0] == '1')
				return (word_move(*s, m->p));
		}
	}
	return (0);
}