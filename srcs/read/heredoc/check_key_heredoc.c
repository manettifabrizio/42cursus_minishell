/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:40:32 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 00:46:43 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		control_heredoc(t_main *m, char *s, char c)
{
	if (c == CTRL_C)
		return (control_c(m, s));
	if (c == CTRL_D && s[0] == '\0')
	{
		m->exit_status = 0;
		return (1);
	}
	return (0);
}

int		check_key_heredoc(t_main *m, char **s, char *buf)
{
	if (buf[0] == CTRL_C || buf[0] == CTRL_D || buf[0] == CTRL_Z)
		return (control_heredoc(m, *s, buf[0]));
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
			if (buf[0] == '1')
				return (word_move(*s, m->pos));
		}
	}
	return (0);
}