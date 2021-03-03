/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:21:23 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/03 20:31:39 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		home_end(char *s, char c, t_cursor *pos)
{
	if (c == HOME)
		return (home(s, pos));
	if (c == END)
		return (end(pos));
	return (0);
}

static int		arrows(t_main *m, char **s, char c)
{
	if (c == ARR_UP)
		return (arrow_up(s, m->hist, m->pos));
	if (c == ARR_DOWN)
		return (arrow_down(s, m->hist, m->pos));
	if (c == ARR_RIGHT)
		return (arrow_right(m->pos));
	if (c == ARR_LEFT)
		return (arrow_left(*s, m->pos));
	return (0);
}

static int		control(t_main *m, char *s, char c)
{
	if (c == CTRL_C)
		return (control_c(m, s));
	if (c == CTRL_D && s[0] == '\0')
		return (control_d(m));
	// if (c == CTRL_Z && s[0] == '\0')
	// 	return (1);
	return (0);
}

int		check_key(t_main *m, char **s, char *buf)
{
	if (buf[0] == CTRL_C || buf[0] == CTRL_D || buf[0] == CTRL_Z)
		return (control(m, *s, buf[0]));
	if (buf[0] == BACKSPACE)
		return (backspace(*s, *(m->pos)));
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
				return (delete(*s, buf, m->pos));
			if (buf[0] == HOME || buf[0] == END)
				return (home_end(*s, buf[0], m->pos));
		}
	}
	return (0);
}