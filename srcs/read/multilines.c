/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:09:55 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/02 12:24:59 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		how_many(char *s, char c)
{
	int		i;
	int		x;

	i = -1;
	x = 0;
	while (s[++i])
		if (s[i] == c)
			x++;
	return (x);
}

static char		check_multi(char *s)
{
	if (how_many(s, '\'') % 2 != 0)
		return ('\'');
	if (how_many(s, '\`') % 2 != 0)
		return ('\`');
	if (how_many(s, '\"') % 2 != 0)
		return ('\"');
	return (0);
}

t_uint		multilines(t_main *m, char *s, char *buf)
{
// 	bash-3.2$ echo "asdafasdfsdf
// 	> bash: unexpected EOF while looking for matching `"'
// 	bash: syntax error: unexpected end of file
	check_multi(s);
	while (buf[0] != c)
	{
		m->hist = history(s, m->hist, i++, m->pos->y);
		read(STDOUT_FILENO, buf, 1);
		if (check_key(&s, buf, m))
		{
			if (buf[0] == CTRL_C)
				break;
		}
		// without if backspace character is added to s
		else
			s = str_print_and_handle(s, buf, *(m->pos));
		m->multi = multilines(s, buf);
	}
}